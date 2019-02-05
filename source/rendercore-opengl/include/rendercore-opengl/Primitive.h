
#pragma once


#include <rendercore/GpuObject.h>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Primitive
*/
class RENDERCORE_OPENGL_API Primitive : public rendercore::GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    Primitive(GpuContainer * container = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Primitive();

protected:
    // Virtual GpuObject functions
    virtual void onInit() override;
    virtual void onDeinit() override;
};


} // namespace opengl
} // namespace rendercore
