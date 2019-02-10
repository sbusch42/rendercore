
#version 330
#extension GL_ARB_explicit_attrib_location : require


// Uniforms
uniform mat4 modelViewProjectionMatrix;


// Inputs
layout (location = 0) in vec3 vertex;
layout (location = 3) in vec2 texcoord;


// Outputs
out vec2 v_texcoord;


void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    v_texcoord  = texcoord;
}
