
#pragma once


#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Attribute indices for specific types of data
*
*  @remarks
*    This is a convention followed by the standard mesh renderers.
*    If you use your own geometry and shaders, feel free to use
*    any other convention you like.
*/
enum class AttributeIndex : unsigned int
{
    Position = 0, ///< Vertex positions (vec3)
    Normal,       ///< Normalized normal vectors (vec3)
    Tangent,      ///< Tangent vectors (vec4)
    TexCoord0,    ///< Texture coordinates #1 (vec2)
    TexCoord1,    ///< Texture coordinates #2 (vec2)
    TexCoord2,    ///< Texture coordinates #3 (vec2)
    TexCoord3,    ///< Texture coordinates #4 (vec2)
    Color0,       ///< Vertex colors #1 (vec3/vec4)
    Color1,       ///< Vertex colors #1 (vec3/vec4)
    Color2,       ///< Vertex colors #1 (vec3/vec4)
    Color3        ///< Vertex colors #1 (vec3/vec4)
};


} // namespace opengl
} // namespace rendercore
