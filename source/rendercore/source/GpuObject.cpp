
#include <rendercore/GpuObject.h>

#include <algorithm>
#include <chrono>

#include <rendercore/GpuContainer.h>


namespace rendercore
{


GpuObject::GpuObject(GpuContainer * container)
: m_container(container)
, m_initialized(false)
, m_valid(false)
{
    // Register at container
    if (m_container) {
        m_container->registerObject(this);
    }
}

GpuObject::~GpuObject()
{
    // Unregister from container
    if (m_container) {
        m_container->unregisterObject(this);
    }
}

const GpuContainer * GpuObject::container() const
{
    return m_container;
}

bool GpuObject::initialized() const
{
    return m_initialized;
}

bool GpuObject::valid() const
{
    return m_valid;
}

void GpuObject::init()
{
    if (!m_initialized) {
        onInit();
    }

    m_initialized = true;
}

void GpuObject::deinit()
{
    if (m_initialized) {
        onDeinit();
    }

    m_initialized = false;
}

void GpuObject::setValid(bool valid)
{
    m_valid = valid;
}

void GpuObject::onInit()
{
}

void GpuObject::onDeinit()
{
}


} // namespace rendercore
