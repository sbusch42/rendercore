
#version 330
#extension GL_ARB_explicit_attrib_location : require


// Uniforms
uniform sampler2D baseColorTexture;
uniform bool      baseColorTextureSet = false;
uniform vec4      baseColorFactor     = vec4(1.0f, 1.0f, 1.0f, 1.0f);


// Inputs
in vec2 v_texcoord;


// Outputs
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
