
#pragma once


#include <memory>

#include <globjects/Buffer.h>

#include <rendercore-opengl/Geometry.h>
#include <rendercore-opengl/Icosahedron.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Sphere shape
*/
class RENDERCORE_OPENGL_API Sphere : public Geometry
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] radius
    *    Sphere radius
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Sphere(float radius = 1.0f, bool texCoords = false);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Sphere();

protected:
    std::unique_ptr<Icosahedron>       m_icosahedron; ///< Refinable icosahedron
    std::unique_ptr<globjects::Buffer> m_vertices;    ///< Vertex buffer
    std::unique_ptr<globjects::Buffer> m_texCoords;   ///< Texture coordinate buffer
    std::unique_ptr<globjects::Buffer> m_indices;     ///< Index buffer
};


} // namespace opengl
} // namespace rendercore
