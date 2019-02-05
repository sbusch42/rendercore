
#pragma once


#include <vector>

#include <rendercore/GpuObject.h>


namespace rendercore
{


/**
*  @brief
*    Class that manages GPU data
*
*    This class can be used to manage the construction and destruction
*    of GPU data. It makes sure that data objects, which represent or
*    relate to data on the GPU, are properly initialized or deinitialized,
*    for example when a rendering context has been replaced.
*/
class RENDERCORE_API GpuContainer : public GpuObject
{
    friend class GpuObject;

public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    GpuContainer(GpuContainer * container = nullptr);

    // Copying a GpuContainer is not allowed
    GpuContainer(const GpuContainer &) = delete;

    // Copying a GpuContainer is not allowed
    GpuContainer & operator=(const GpuContainer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~GpuContainer();

    /**
    *  @brief
    *    Get GPU objects
    *
    *  @return
    *    GPU objects
    */
    const std::vector<GpuObject *> & objects() const;

    // Virtual GpuObject functions
    virtual void init() override;
    virtual void deinit() override;

protected:
    // Virtual GpuObject functions
    virtual void onInit() override;
    virtual void onDeinit() override;

    /**
    *  @brief
    *    Initialize all objects
    *
    *  @notes
    *    - Requires an active rendering context
    */
    void initObjects();

    /**
    *  @brief
    *    De-Initialize all objects
    *
    *  @notes
    *    - Requires an active rendering context
    */
    void deinitObjects();

    /**
    *  @brief
    *    Register GPU object
    *
    *  @param[in] object
    *    GPU object (must NOT be null!)
    *
    *  @remarks
    *    By registering an object on a GPU container, it is made sure
    *    that the object will be initialized/deinitialized correctly
    *    when the rendering context has changed, allowing the GPU object
    *    to create its GPU data when a context is active or to restore
    *    it from CPU representations.
    *
    *    GPU objects automatically register themselves in the constructur,
    *    and deregister themselves in the destructor. The relationship
    *    between container and object only affects context management,
    *    it does not imply ownership of objects.
    */
    void registerObject(GpuObject * object);

    /**
    *  @brief
    *    Unregister object
    *
    *  @param[in] object
    *    GPU object (must NOT be null!)
    */
    void unregisterObject(GpuObject * object);

    /**
    *  @brief
    *    Update list of objects (take into account added and removed objects)
    */
    void updateLists();

protected:
    std::vector<GpuObject *> m_objects; ///< GPU objects
    std::vector<GpuObject *> m_added;   ///< GPU objects which have been recently added
    std::vector<GpuObject *> m_removed; ///< GPU objects which have been recently removed
};


} // namespace rendercore
