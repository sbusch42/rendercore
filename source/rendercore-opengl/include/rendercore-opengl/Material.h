
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
    *  @param[in] parent
    *    Parent object (can be null)
    */
    Material(GpuObject * parent = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Material();

protected:
    // Virtual GpuObject functions
    virtual void onContextInit(AbstractContext * context) override;
    virtual void onContextDeinit(AbstractContext * context) override;
};


} // namespace opengl
} // namespace rendercore
