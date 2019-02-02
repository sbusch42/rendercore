
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
*    Quad shape
*/
class RENDERCORE_OPENGL_API Quad : public Geometry
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] size
    *    Edge width and height
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Quad(float size = 2.0f, bool texCoords = false);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] width
    *    Edge width
    *  @param[in] height
    *    Edge height
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Quad(float width, float height, bool texCoords = false);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Quad();

protected:
    std::unique_ptr<globjects::Buffer> m_vertices;  ///< Vertex buffer
    std::unique_ptr<globjects::Buffer> m_texCoords; ///< Texture coordinate buffer
};


} // namespace opengl
} // namespace rendercore
