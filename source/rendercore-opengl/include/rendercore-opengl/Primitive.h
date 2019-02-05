
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
    *  @param[in] parent
    *    Parent object (can be null)
    */
    Primitive(GpuObject * parent = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Primitive();

protected:
    // Virtual GpuObject functions
    virtual void onContextInit(AbstractContext * context) override;
    virtual void onContextDeinit(AbstractContext * context) override;
};


} // namespace opengl
} // namespace rendercore
