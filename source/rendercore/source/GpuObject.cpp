
#include <algorithm>
#include <chrono>

#include <rendercore/GpuObject.h>


namespace rendercore
{


GpuObject::GpuObject(GpuObject * parent)
: m_context(nullptr)
, m_parent(parent)
{
    // Register at parent
    if (m_parent) {
        m_parent->registerObject(this);
    }
}

GpuObject::~GpuObject()
{
    // Unregister from parent
    if (m_parent) {
        m_parent->unregisterObject(this);
    }
}

const GpuObject * GpuObject::parent() const
{
    return m_parent;
}

const std::vector<GpuObject *> & GpuObject::children() const
{
    return m_children;
}

const AbstractContext * GpuObject::context() const
{
    return m_context;
}

AbstractContext * GpuObject::context()
{
    return m_context;
}

void GpuObject::initContext(AbstractContext * context)
{
    // Check if object is already attached to this context
    if (m_context == context) {
        return;
    }

    // Check if object is attached to another context
    if (m_context != nullptr) {
        return;
    }

    // Initialize new context
    if (context) {
        // Save context
        m_context = context;

        // Initialize object in context
        onContextInit(context);
    }

    // Initialize child objects
    for (GpuObject * object : m_children) {
        object->initContext(context);
    }
}

void GpuObject::deinitContext(AbstractContext * context)
{
    // De-initialize child objects
    for (GpuObject * object : m_children) {
        object->deinitContext(context);
    }

    // Check if object is attached to the context
    if (m_context != context) {
        return;
    }

    // Deinitialize context
    if (m_context) {
        // Deinitialize object in context
        onContextDeinit(context);

        // Reset context
        m_context = nullptr;
    }
}

void GpuObject::registerObject(GpuObject * object)
{
    // Check that object is not already registered
    if (std::find(m_children.begin(), m_children.end(), object) == m_children.end()) {
        m_children.push_back(object);
    }
}

void GpuObject::unregisterObject(GpuObject * object)
{
    // Find object in list
    auto it = std::find(m_children.begin(), m_children.end(), object);
    if (it != m_children.end()) {
        // Remove object from list
        m_children.erase(it);
    }
}


} // namespace rendercore
