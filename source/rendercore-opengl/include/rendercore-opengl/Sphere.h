
#pragma once


#include <rendercore-opengl/Mesh.h>
#include <rendercore-opengl/Icosahedron.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Sphere shape
*/
class RENDERCORE_OPENGL_API Sphere : public Mesh
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    *  @param[in] radius
    *    Sphere radius
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Sphere(GpuContainer * container = nullptr, float radius = 1.0f, bool texCoords = false);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Sphere();

protected:
    std::unique_ptr<Icosahedron> m_icosahedron; ///< Refinable icosahedron
};


} // namespace opengl
} // namespace rendercore
