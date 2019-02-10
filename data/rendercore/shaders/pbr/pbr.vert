
// Originally taken from https://github.com/KhronosGroup/glTF-WebGL-PBR
// Commit c28b5b8f5a83380857ad8395ac5302594ecc13ae


#version 330
#extension GL_ARB_explicit_attrib_location : require


// Uniforms
uniform bool hasColors    = false;
uniform bool hasTexCoords = false;
uniform bool hasNormals   = false;
uniform bool hasTangents  = false;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;
uniform mat3 normalMatrix;


// Inputs
layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 tangent;
layout (location = 3) in vec2 texcoord0;
layout (location = 4) in vec2 texcoord1;
layout (location = 7) in vec4 color;


// Outputs
out vec3 v_position;
out vec2 v_uv[2];
out vec4 v_color;
out mat3 v_tbn;
out vec3 v_normal;


void main()
{
    // Get position in world space
    vec4 pos = modelMatrix * position;
    v_position = vec3(pos.xyz) / pos.w;

    // Get normal vector
    if (hasNormals) {
        if (hasTangents) {
            // Calculate TBN matrix
            vec3 normalW = normalize(vec3(normalMatrix * normal));
            vec3 tangentW = normalize(vec3(modelMatrix * vec4(tangent.xyz, 0.0)));
            vec3 bitangentW = cross(normalW, tangentW) * tangent.w;
            v_tbn = mat3(tangentW, bitangentW, normalW);
        } else {
            // Only transform normal vector
            v_normal = normalize(vec3(modelMatrix * vec4(normal.xyz, 0.0)));
        }
    } else {
        // Assuming a model that is centered around the origin, calculate normal in world space (and then camera space)
        vec4 center = modelMatrix * vec4(0.0, 0.0, 0.0, 1.0);
        v_normal = normalize(vec3(normalMatrix * normalize(v_position - center.xyz)));
    }

    // Texture texture coordinates
    if (hasTexCoords) {
        v_uv[0] = texcoord0;
        v_uv[1] = texcoord1;
    } else {
        v_uv[0] = vec2(0.0, 0.0);
        v_uv[1] = vec2(0.0, 0.0);
    }

    // Get color
    if (hasColors) {
        v_color = color;
    } else {
        v_color = vec4(1.0, 1.0, 1.0, 1.0);
    }

    // Transform position into screen space
    gl_Position = viewProjectionMatrix * modelMatrix * position;
}
