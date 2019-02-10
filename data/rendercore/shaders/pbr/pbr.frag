
// Originally taken from https://github.com/KhronosGroup/glTF-WebGL-PBR
// Commit c28b5b8f5a83380857ad8395ac5302594ecc13ae

// This fragment shader defines a reference implementation for Physically Based Shading of
// a microfacet surface material defined by a glTF model.

// References:
// [1] Real Shading in Unreal Engine 4
//     http://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf
// [2] Physically Based Shading at Disney
//     http://blog.selfshadow.com/publications/s2012-shading-course/burley/s2012_pbs_disney_brdf_notes_v3.pdf
// [3] README.md - Environment Maps
//     https://github.com/KhronosGroup/glTF-WebGL-PBR/#environment-maps
// [4] "An Inexpensive BRDF Model for Physically based Rendering" by Christophe Schlick
//     https://www.cs.virginia.edu/~jdl/bib/appearance/analytic%20models/schlick94b.pdf


#version 330
#extension GL_ARB_explicit_attrib_location : require


// Definitions
// #define USE_IBL
// #define USE_TEX_LOD


// Constants
const float M_PI = 3.141592653589793;
const float c_MinRoughness = 0.04;


// Uniforms
uniform bool hasColors                = false;
uniform bool hasTexCoords             = false;
uniform bool hasTangents              = false;
uniform bool hasBaseColorTexture      = false;
uniform bool hasMetalRoughnessTexture = false;
uniform bool hasNormalTexture         = false;
uniform bool hasOcclusionTexture      = false;
uniform bool hasEmissiveTexture       = false;

uniform sampler2D baseColorTexture;
uniform sampler2D metallicRoughnessTexture;
uniform sampler2D normalTexture;
uniform sampler2D occlusionTexture;
uniform sampler2D emissiveTexture;
#ifdef USE_IBL
    uniform samplerCube diffuseEnvTexture;
    uniform samplerCube specularEnvTexture;
    uniform sampler2D   brdfLUTTexture;
#endif

uniform int baseColorUVIndex         = 0;
uniform int normalUVIndex            = 0;
uniform int emissiveUVIndex          = 0;
uniform int metallicRoughnessUVIndex = 0;
uniform int occlusionUVIndex         = 0;

uniform vec4  baseColorFactor   = vec4(1.0, 1.0, 1.0, 1.0);
uniform float metallicFactor    = 1.0;
uniform float roughnessFactor   = 1.0;
uniform vec3  emissiveFactor    = vec3(0.0, 0.0, 0.0);
uniform float alphaBlendEnabled = 1.0;
uniform float alphaCutoff       = 0.5;
uniform float normalScale       = 1.0;
uniform float occlusionStrength = 1.0;

uniform vec3  eyePosition           = vec3(0.0, 0.0, 0.0);
uniform vec3  lightPosition         = vec3(0.0, 0.0, 0.0);
uniform vec3  lightColor            = vec3(1.0, 1.0, 1.0);
uniform vec3  ambientLightColor     = vec3(1.0, 1.0, 1.0);
uniform float ambientLightIntensity = 1.0;

// Debugging flags used for shader output of intermediate PBR variables
uniform vec4 scaleDiffBaseMR = vec4(1.0);
uniform vec4 scaleFGDSpec    = vec4(1.0);
uniform vec4 scaleIBLAmbient = vec4(1.0);


// Vertex attributes
in vec3 v_position;
in vec2 v_uv[2];
in vec4 v_color;
in mat3 v_tbn;
in vec3 v_normal;


// Outputs
layout(location = 0) out vec4 fragColor;


// Encapsulate the various inputs used by the various functions in the shading equation
// We store values in this struct to simplify the integration of alternative implementations
// of the shading terms, outlined in the Readme.MD Appendix.
struct PBRInfo
{
    float NdotL;                  // cos angle between normal and light direction
    float NdotV;                  // cos angle between normal and view direction
    float NdotH;                  // cos angle between normal and half vector
    float LdotH;                  // cos angle between light direction and half vector
    float VdotH;                  // cos angle between view direction and half vector
    float perceptualRoughness;    // roughness value, as authored by the model creator (input to shader)
    float metalness;              // metallic value at the surface
    vec3 reflectance0;            // full reflectance color (normal incidence angle)
    vec3 reflectance90;           // reflectance color at grazing angle
    float alphaRoughness;         // roughness mapped to a more linear change in the roughness (proposed by [2])
    vec3 diffuseColor;            // color contribution from diffuse lighting
    vec3 specularColor;           // color contribution from specular lighting
};

vec4 SRGBtoLINEAR(vec4 srgbIn)
{
    #ifdef MANUAL_SRGB
        #ifdef SRGB_FAST_APPROXIMATION
            vec3 linOut = pow(srgbIn.xyz,vec3(2.2));
        #else //SRGB_FAST_APPROXIMATION
            vec3 bLess = step(vec3(0.04045),srgbIn.xyz);
            vec3 linOut = mix( srgbIn.xyz/vec3(12.92), pow((srgbIn.xyz+vec3(0.055))/vec3(1.055),vec3(2.4)), bLess );
        #endif //SRGB_FAST_APPROXIMATION

        return vec4(linOut,srgbIn.w);;
    #else //MANUAL_SRGB
        return srgbIn;
    #endif //MANUAL_SRGB
}

// Find the normal for this fragment, pulling either from a predefined normal map
// or from the interpolated mesh normal and tangent attributes.
vec3 getNormal()
{
    // [TODO]
    if (!hasTangents && !hasTexCoords) {
        return normalize(v_normal);
    }

    // Retrieve the tangent space matrix
    mat3 tbn;
    if (hasTangents) {
        tbn = v_tbn;
    } else {
        // Calculate from positions and uv-coordinates
        vec3 pos_dx = dFdx(v_position);
        vec3 pos_dy = dFdy(v_position);
        vec3 tex_dx = dFdx(vec3(v_uv[0], 0.0));
        vec3 tex_dy = dFdy(vec3(v_uv[0], 0.0));
        vec3 t = (tex_dy.t * pos_dx - tex_dx.t * pos_dy) / (tex_dx.s * tex_dy.t - tex_dy.s * tex_dx.t);

        vec3 ng = normalize(v_normal);

        t = normalize(t - ng * dot(ng, t));
        vec3 b = normalize(cross(ng, t));
        tbn = mat3(t, b, ng);
    }

    vec3 n;
    if (hasNormalTexture) {
        n = texture(normalTexture, v_uv[normalUVIndex]).rgb;
        n = normalize(tbn * ((2.0 * n - 1.0) * vec3(normalScale, normalScale, 1.0)));
    } else {
        // The tbn matrix is linearly interpolated, so we need to re-normalize
        n = normalize(tbn[2].xyz);
    }

    // reverse backface normals
    n *= (2.0 * float(gl_FrontFacing) - 1.0);

    return n;
}

// Calculation of the lighting contribution from an optional Image Based Light source.
// Precomputed Environment Maps are required uniform inputs and are computed as outlined in [1].
// See our README.md on Environment Maps [3] for additional discussion.
#ifdef USE_IBL
vec3 getIBLContribution(PBRInfo pbrInputs, vec3 n, vec3 reflection)
{
    float mipCount = 9.0; // resolution of 512x512
    float lod = (pbrInputs.perceptualRoughness * mipCount);
    // retrieve a scale and bias to F0. See [1], Figure 3
    vec3 brdf = SRGBtoLINEAR(texture(brdfLUTTexture, vec2(pbrInputs.NdotV, 1.0 - pbrInputs.perceptualRoughness))).rgb;
    vec3 diffuseLight = SRGBtoLINEAR(textureCube(diffuseEnvTexture, n)).rgb;

#ifdef USE_TEX_LOD
    vec3 specularLight = SRGBtoLINEAR(textureCubeLodEXT(specularEnvTexture, reflection, lod)).rgb;
#else
    vec3 specularLight = SRGBtoLINEAR(textureCube(specularEnvTexture, reflection)).rgb;
#endif

    vec3 diffuse = diffuseLight * pbrInputs.diffuseColor;
    vec3 specular = specularLight * (pbrInputs.specularColor * brdf.x + brdf.y);

    // For presentation, this allows us to disable IBL terms
    diffuse *= scaleIBLAmbient.x;
    specular *= scaleIBLAmbient.y;

    return diffuse + specular;
}
#endif

// Basic Lambertian diffuse
// Implementation from Lambert's Photometria https://archive.org/details/lambertsphotome00lambgoog
// See also [1], Equation 1
vec3 diffuse(PBRInfo pbrInputs)
{
    return pbrInputs.diffuseColor / M_PI;
}

// The following equation models the Fresnel reflectance term of the spec equation (aka F())
// Implementation of fresnel from [4], Equation 15
vec3 specularReflection(PBRInfo pbrInputs)
{
    return pbrInputs.reflectance0 + (pbrInputs.reflectance90 - pbrInputs.reflectance0) * pow(clamp(1.0 - pbrInputs.VdotH, 0.0, 1.0), 5.0);
}

// This calculates the specular geometric attenuation (aka G()),
// where rougher material will reflect less light back to the viewer.
// This implementation is based on [1] Equation 4, and we adopt their modifications to
// alphaRoughness as input as originally proposed in [2].
float geometricOcclusion(PBRInfo pbrInputs)
{
    float NdotL = pbrInputs.NdotL;
    float NdotV = pbrInputs.NdotV;
    float r = pbrInputs.alphaRoughness;

    float attenuationL = 2.0 * NdotL / (NdotL + sqrt(r * r + (1.0 - r * r) * (NdotL * NdotL)));
    float attenuationV = 2.0 * NdotV / (NdotV + sqrt(r * r + (1.0 - r * r) * (NdotV * NdotV)));
    return attenuationL * attenuationV;
}

// The following equation(s) model the distribution of microfacet normals across the area being drawn (aka D())
// Implementation from "Average Irregularity Representation of a Roughened Surface for Ray Reflection" by T. S. Trowbridge, and K. P. Reitz
// Follows the distribution function recommended in the SIGGRAPH 2013 course notes from EPIC Games [1], Equation 3.
float microfacetDistribution(PBRInfo pbrInputs)
{
    float roughnessSq = pbrInputs.alphaRoughness * pbrInputs.alphaRoughness;
    float f = (pbrInputs.NdotH * roughnessSq - pbrInputs.NdotH) * pbrInputs.NdotH + 1.0;
    return roughnessSq / (M_PI * f * f);
}

void main()
{
    // fragColor = vec4(1.0, 0.0, 0.0, 1.0);

    // Metallic and Roughness material properties are packed together
    // In glTF, these factors can be specified by fixed scalar values
    // or from a metallic-roughness map
    float perceptualRoughness = roughnessFactor;
    float metallic = metallicFactor;

    if (hasMetalRoughnessTexture) {
        // Roughness is stored in the 'g' channel, metallic is stored in the 'b' channel.
        // This layout intentionally reserves the 'r' channel for (optional) occlusion map data
        vec4 mrSample = texture(metallicRoughnessTexture, v_uv[metallicRoughnessUVIndex]);
        perceptualRoughness = mrSample.g * perceptualRoughness;
        metallic = mrSample.b * metallic;
    }

    perceptualRoughness = clamp(perceptualRoughness, c_MinRoughness, 1.0);
    metallic = clamp(metallic, 0.0, 1.0);

    // Roughness is authored as perceptual roughness; as is convention,
    // convert to material roughness by squaring the perceptual roughness [2].
    float alphaRoughness = perceptualRoughness * perceptualRoughness;

    // The albedo may be defined from a base texture or a flat color
    vec4 baseColor;
    if (hasBaseColorTexture) {
        baseColor = SRGBtoLINEAR(texture(baseColorTexture, v_uv[baseColorUVIndex])) * baseColorFactor;
    } else {
        baseColor = baseColorFactor;
    }

    // spec: COLOR_0 ... acts as an additional linear multiplier to baseColor
    // [TODO] Distinguish between vec3/vec4 colors ...
    baseColor *= vec4(v_color.rgb, 1.0);

    vec3 f0 = vec3(0.04);
    vec3 diffuseColor = baseColor.rgb * (vec3(1.0) - f0);
    diffuseColor *= 1.0 - metallic;
    vec3 specularColor = mix(f0, baseColor.rgb, metallic);

    // Compute reflectance.
    float reflectance = max(max(specularColor.r, specularColor.g), specularColor.b);

    // For typical incident reflectance range (between 4% to 100%) set the grazing reflectance to 100% for typical fresnel effect.
    // For very low reflectance range on highly diffuse objects (below 4%), incrementally reduce grazing reflecance to 0%.
    float reflectance90 = clamp(reflectance * 25.0, 0.0, 1.0);
    vec3 specularEnvironmentR0 = specularColor.rgb;
    vec3 specularEnvironmentR90 = vec3(1.0, 1.0, 1.0) * reflectance90;

    vec3 n = getNormal();                           // normal at surface point
    vec3 v = normalize(eyePosition - v_position);   // Vector from surface point to camera
    vec3 l = normalize(lightPosition - v_position); // Vector from surface point to light
    vec3 h = normalize(l + v);                      // Half vector between both l and v
    vec3 reflection = -normalize(reflect(v, n));

    float NdotL = clamp(dot(n, l), 0.001, 1.0);
    float NdotV = abs(dot(n, v)) + 0.001;
    float NdotH = clamp(dot(n, h), 0.0, 1.0);
    float LdotH = clamp(dot(l, h), 0.0, 1.0);
    float VdotH = clamp(dot(v, h), 0.0, 1.0);

    PBRInfo pbrInputs = PBRInfo(
        NdotL,
        NdotV,
        NdotH,
        LdotH,
        VdotH,
        perceptualRoughness,
        metallic,
        specularEnvironmentR0,
        specularEnvironmentR90,
        alphaRoughness,
        diffuseColor,
        specularColor
    );

    // Calculate the shading terms for the microfacet specular shading model
    vec3  F = specularReflection(pbrInputs);
    float G = geometricOcclusion(pbrInputs);
    float D = microfacetDistribution(pbrInputs);

    // Calculation of analytical lighting contribution
    vec3 diffuseContrib = (1.0 - F) * diffuse(pbrInputs);
    vec3 specContrib = F * G * D / (4.0 * NdotL * NdotV);
    // Obtain final intensity as reflectance (BRDF) scaled by the energy of the light (cosine law)
    vec3 color = NdotL * lightColor * (diffuseContrib + specContrib);

    // Calculate lighting contribution from image based lighting source (IBL)
#ifdef USE_IBL
    color += getIBLContribution(pbrInputs, n, reflection);
#else
    // Add simple ambient light
    color += ambientLightColor * ambientLightIntensity * baseColor.xyz;
#endif

    // Apply optional PBR terms for additional (optional) shading
    if (hasOcclusionTexture) {
        float ao = texture(occlusionTexture, v_uv[occlusionUVIndex]).r;
        color = mix(color, color * ao, occlusionStrength);
    }

    if (hasEmissiveTexture) {
        vec3 emissive = SRGBtoLINEAR(texture(emissiveTexture, v_uv[emissiveUVIndex])).rgb * emissiveFactor;
        color += emissive;
    }

    // This section uses mix to override final color for reference app visualization
    // of various parameters in the lighting equation.
    // color = mix(color, F, scaleFGDSpec.x);
    // color = mix(color, vec3(G), scaleFGDSpec.y);
    // color = mix(color, vec3(D), scaleFGDSpec.z);
    // color = mix(color, specContrib, scaleFGDSpec.w);

    // color = mix(color, diffuseContrib, scaleDiffBaseMR.x);
    // color = mix(color, baseColor.rgb, scaleDiffBaseMR.y);
    // color = mix(color, vec3(metallic), scaleDiffBaseMR.z);
    // color = mix(color, vec3(perceptualRoughness), scaleDiffBaseMR.w);

    // NOTE: the spec mandates to ignore any alpha value in 'OPAQUE' mode
    float alpha = mix(1.0, baseColor.a, alphaBlendEnabled);
    if (alphaCutoff > 0.0) {
        alpha = step(alphaCutoff, baseColor.a);
    }

    fragColor = vec4(pow(color, vec3(1.0 / 2.2)), alpha);
}
