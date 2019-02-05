
#pragma once


#include <rendercore/rendercore_api.h>


namespace rendercore
{


class GpuContainer;


/**
*  @brief
*    Base class for objects that represent or reference GPU data
*/
class RENDERCORE_API GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    GpuObject(GpuContainer * container = nullptr);

    // Copying a GpuObject is not allowed
    GpuObject(const GpuObject &) = delete;

    // Copying a GpuObject is not allowed
    GpuObject & operator=(const GpuObject &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~GpuObject();

    /**
    *  @brief
    *    Get container
    *
    *  @return
    *    Container to which the object belongs (can be null)
    */
    const GpuContainer * container() const;

    /**
    *  @brief
    *    Check if GPU object has been initialized
    *
    *  @return
    *    'true' if initialized in current context, else 'false'
    */
    bool initialized() const;

    /**
    *  @brief
    *    Check if GPU object if valid or needs update (e.g., because data has been modified)
    *
    *  @return
    *    'true' if GPU object is valid, else 'false'
    */
    bool valid() const;

    /**
    *  @brief
    *    Initialize GPU object in current rendering context
    *
    *  @notes
    *    - Requires an active rendering context
    */
    virtual void init();

    /**
    *  @brief
    *    De-Initialize GPU object in current rendering context
    *
    *  @notes
    *    - Requires an active rendering context
    */
    virtual void deinit();

protected:
    /**
    *  @brief
    *    Set if GPU object is valid
    *
    *  @param[in]
    *    'true' if GPU object is valid, else 'false'
    */
    void setValid(bool valid);

    /**
    *  @brief
    *    Called when the GPU object is initialized
    */
    virtual void onInit();

    /**
    *  @brief
    *    Called when the GPU object is de-initialized
    */
    virtual void onDeinit();

protected:
    GpuContainer * m_container;   ///< Container to which the object belongs (never null)
    bool           m_initialized; ///< 'true' if initialized in current context, else 'false'

private:
    bool m_valid; ///< 'true' if GPU object is valid, else 'false'
};


} // namespace rendercore
