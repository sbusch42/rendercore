
#pragma once


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
    *  @param[in] container
    *    GPU container (can be null)
    *  @param[in] size
    *    Edge width and height
    *  @param[in] texCoords
    *    Generate texture coordinates?
    */
    Triangle(GpuContainer * container = nullptr, float size = 2.0f, bool texCoords = false);

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
    Triangle(GpuContainer * container, float width, float height, bool texCoords = false);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Triangle();
};


} // namespace opengl
} // namespace rendercore
