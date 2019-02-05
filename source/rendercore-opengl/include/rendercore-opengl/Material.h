
#pragma once


#include <rendercore/GpuObject.h>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Material
*/
class RENDERCORE_OPENGL_API Material : public rendercore::GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    Material(GpuContainer * container = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Material();

protected:
    // Virtual GpuObject functions
    virtual void onInit() override;
    virtual void onDeinit() override;
};


} // namespace opengl
} // namespace rendercore
