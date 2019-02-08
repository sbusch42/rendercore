
#pragma once


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
    *  @param[in] container
    *    GPU container (can be null)
    *  @param[in] size
    *    Edge width, height, and depth
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Box(GpuContainer * container = nullptr, float size = 2.0f, bool texCoords = false);

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
    *  @param[in] depth
    *    Edge depth
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Box(GpuContainer * container, float width, float height, float depth, bool texCoords = false);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Box();
};


} // namespace opengl
} // namespace rendercore
