
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
*    Triangle shape
*/
class RENDERCORE_OPENGL_API Triangle : public Geometry
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
    Triangle(float size = 2.0f, bool texCoords = false);

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
    Triangle(float width, float height, bool texCoords = false);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Triangle();

protected:
    std::unique_ptr<globjects::Buffer> m_vertices;  ///< Vertex buffer
    std::unique_ptr<globjects::Buffer> m_texCoords; ///< Texture coordinate buffer
};


} // namespace opengl
} // namespace rendercore
