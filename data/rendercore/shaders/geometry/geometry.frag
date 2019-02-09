
#version 330
#extension GL_ARB_explicit_attrib_location : require


uniform sampler2D baseColorTexture;
uniform bool      baseColorTextureSet = false;
uniform vec4      baseColorFactor     = vec4(1.0f, 1.0f, 1.0f, 1.0f);


in vec2 v_texcoord;


layout (location = 0) out vec4 colorOut;


void main()
{
    // Output color
    if (baseColorTextureSet) {
        colorOut = texture(baseColorTexture, v_texcoord) * baseColorFactor;
    } else {
        colorOut = baseColorFactor;
    }
}
