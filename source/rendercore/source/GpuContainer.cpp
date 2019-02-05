
#include <rendercore/GpuContainer.h>

#include <algorithm>

#include <cppassist/logging/logging.h>

#include <rendercore/GpuObject.h>


namespace rendercore
{


GpuContainer::GpuContainer(GpuContainer * container)
: GpuObject(container)
{
}

GpuContainer::~GpuContainer()
{
}

const std::vector<GpuObject *> & GpuContainer::objects() const
{
    return m_objects;
}

void GpuContainer::init()
{
    // Initialize objects
    if (!m_initialized) {
        initObjects();
    }

    // Go on
    GpuObject::init();
}

void GpuContainer::deinit()
{
    // De-Initialize objects
    if (m_initialized) {
        deinitObjects();
    }

    // Go on
    GpuObject::deinit();
}

void GpuContainer::onInit()
{
}

void GpuContainer::onDeinit()
{
}

void GpuContainer::initObjects()
{
    // Object can be added or removed during the initialization, therefore, this loop
    do {
        // Update object list
        updateLists();

        // Make sure that all objects are initialized
        for (GpuObject * object : m_objects) {
            object->init();
        }
    } while (!m_added.empty());
}

void GpuContainer::deinitObjects()
{
    // Include newly added objects
    m_objects.insert(m_objects.end(), m_added.begin(), m_added.end());
    m_added.clear();

    // Make sure that all objects are de-initialized
    for (GpuObject * object : m_objects) {
        object->deinit();
    }
}

void GpuContainer::registerObject(GpuObject * object)
{
    // Check that object is not already registered
    if (std::find(m_objects.begin(), m_objects.end(), object) == m_objects.end() &&
        std::find(m_added.begin(),   m_added.end(),   object) == m_added.end())
    {
        m_added.push_back(object);
    }
}

void GpuContainer::unregisterObject(GpuObject * object)
{
    // Check that object is in either m_objects or m_added
    if (std::find(m_objects.begin(), m_objects.end(), object) == m_objects.end()) {
        if (std::find(m_added.begin(), m_added.end(), object) == m_added.end()) {
            // Object not found
            return;
        }
    }

    // Check that object is not yet on the remove list
    auto it = std::find(m_removed.begin(), m_removed.end(), object);
    if (it == m_removed.end()) {
        // Add object to be removed
        m_removed.push_back(object);
    }
}

void GpuContainer::updateLists()
{
    // Include newly added objects
    m_objects.insert(m_objects.end(), m_added.begin(), m_added.end());

    // Remove objects
    for (auto * obj : m_removed) {
        // Find object in m_objects
        auto it = std::find(m_objects.begin(), m_objects.end(), obj);
        if (it != m_objects.end()) {
            // Remove object from list
            m_objects.erase(it);
        }
    }

    // Reset lists
    m_added.clear();
    m_removed.clear();
}


} // namespace rendercore
