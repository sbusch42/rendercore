
#pragma once


#include <rendercore-opengl/Mesh.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Quad shape
*/
class RENDERCORE_OPENGL_API Quad : public Mesh
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    *  @param[in] size
    *    Edge width and height
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Quad(GpuContainer * container = nullptr, float size = 2.0f, bool texCoords = false);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    *  @param[in] width
    *    Edge width
    *  @param[in] height
    *    Edge height
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Quad(GpuContainer * container, float width, float height, bool texCoords = false);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Quad();
};


} // namespace opengl
} // namespace rendercore
