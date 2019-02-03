
#pragma once


#include <vector>

#include <rendercore/rendercore_api.h>


namespace rendercore
{


class AbstractContext;


/**
*  @brief
*    Base class for objects that represent GPU data
*/
class RENDERCORE_API GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] parent
    *    Parent object (can be null)
    */
    GpuObject(GpuObject * parent);

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
    *    Get parent object
    *
    *  @return
    *    Parent object (can be null)
    */
    const GpuObject * parent() const;

    /**
    *  @brief
    *    Get child objects
    *
    *  @return
    *    Child objects
    */
    const std::vector<GpuObject *> & children() const;

    /**
    *  @brief
    *    Get rendering context
    *
    *  @return
    *    Rendering context (can be null)
    */
    const AbstractContext * context() const;

    /**
    *  @brief
    *    Get rendering context
    *
    *  @return
    *    Rendering context (can be null)
    */
    AbstractContext * context();

    /**
    *  @brief
    *    Initialize in rendering context
    *
    *  @param[in] context
    *    Rendering context (must NOT null!)
    *
    *  @see onContextInit
    */
    void initContext(AbstractContext * context);

    /**
    *  @brief
    *    De-Initialize in rendering context
    *
    *  @param[in] context
    *    Rendering context (must NOT null!)
    *
    *  @see onContextDeinit
    */
    void deinitContext(AbstractContext * context);

protected:
    /**
    *  @brief
    *    Register sub-object
    *
    *  @param[in] object
    *    GPU object (must NOT be null!)
    *
    *  @remarks
    *    By registering a sub-object on a GPU object, it is made sure
    *    that the sub-object's initContext/deinitContext-methods will
    *    be called automatically when called on the parent object.
    *    GPU objects automatically register themselves at their parent
    *    object, when you pass the parent object in the constructur,
    *    and deregister themselves in the destructor.
    *    The parent/child-relationship only affects context initialization,
    *    it does not imply ownership of objects.
    */
    void registerObject(GpuObject * object);

    /**
    *  @brief
    *    Unregister sub-object
    *
    *  @param[in] object
    *    GPU object (must NOT be null!)
    */
    void unregisterObject(GpuObject * object);

    /**
    *  @brief
    *    Called when the renderer is initialized in a new rendering context
    *
    *  @param[in] context
    *    Rendering context (never null)
    *
    *  @remarks
    *    Use this function to initialize all GPU objects, or use lazy
    *    initialization and initialize them on the first rendering call.
    *    Do not store them as direct members of the class, as they must
    *    be de-initialized in onContextDeinit(), not on the call of the
    *    destructor. This method can also be used to restore GPU objects
    *    from CPU data, when a context switch has occured.
    */
    virtual void onContextInit(AbstractContext * context) = 0;

    /**
    *  @brief
    *    Called when the renderer is de-initialized in its rendering context
    *
    *  @param[in] context
    *    Rendering context (never null)
    *
    *  @remarks
    *    Use this function to de-initialize all GPU objects. It is
    *    important to do it here instead of the destructor, because
    *    this needs the context to still be active, which is guaranteed
    *    only in this function. This method can also be used to backup
    *    data from GPU objects into CPU data, which can later be restored
    *    when a context switch has occured.
    */
    virtual void onContextDeinit(AbstractContext * context) = 0;

protected:
    AbstractContext          * m_context;  ///< Rendering context (can be null)
    GpuObject                * m_parent;   ///< Parent object of this GPU object (can be null)
    std::vector<GpuObject *>   m_children; ///< Child objects of this GPU object
};


} // namespace rendercore
