
#version 330
#extension GL_ARB_explicit_attrib_location : require


layout (location = 0) out vec4 colorOut;


void main()
{
    // Output color
    colorOut = vec4(0.0, 1.0, 0.0, 1.0);
}
