
#version 330
#extension GL_ARB_explicit_attrib_location : require


// Inputs
in vec3 v_color;


// Outputs
layout (location = 0) out vec4 colorOut;


void main()
{
    // Output color
    colorOut = vec4(v_color, 1.0);
}
