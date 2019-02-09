
#version 330
#extension GL_ARB_explicit_attrib_location : require


uniform mat4 modelViewProjectionMatrix;


layout (location = 0) in vec3 vertex;


void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
