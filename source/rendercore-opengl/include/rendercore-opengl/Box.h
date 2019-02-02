
#pragma once


#include <memory>

#include <globjects/Buffer.h>

#include <rendercore-opengl/Geometry.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Box shape
*/
class RENDERCORE_OPENGL_API Box : public Geometry
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] size
    *    Edge width, height, and depth
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Box(float size = 2.0f, bool texCoords = false);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] width
    *    Edge width
    *  @param[in] height
    *    Edge height
    *  @param[in] depth
    *    Edge depth
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Box(float width, float height, float depth, bool texCoords = false);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Box();

protected:
    std::unique_ptr<globjects::Buffer> m_vertices;  ///< Vertex buffer
    std::unique_ptr<globjects::Buffer> m_texCoords; ///< Texture coordinate buffer
};


} // namespace opengl
} // namespace rendercore
