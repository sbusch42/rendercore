
#include <rendercore-opengl/Buffer.h>

#include <algorithm>
#include <cstring>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>
#include <glbinding/gl/enum.h>


namespace rendercore
{
namespace opengl
{


Buffer::Buffer(GpuContainer * container)
: GpuObject(container)
{
}

Buffer::~Buffer()
{
}

unsigned int Buffer::size() const
{
    return m_data.size();
}

const char * Buffer::data() const
{
    return m_data.data();
}

char * Buffer::data()
{
    return m_data.data();
}

void Buffer::setData(const void * data, unsigned int size)
{
    // Clear old data
    m_data.clear();

    // Check if data is valid
    if (!data || size == 0) {
        return;
    }

    // Allocate data
    m_data.resize(size);

    // Copy data
    std::memcpy(m_data.data(), data, size);

    // Flag buffer invalid
    setValid(false);
}

void Buffer::allocate(unsigned int size)
{
    // Clear old data
    m_data.clear();

    // Set new size
    m_data.resize(size);

    // Flag buffer invalid
    setValid(false);
}

globjects::Buffer * Buffer::buffer()
{
    // Check if buffer needs to be updated or restored
    if (!m_buffer.get() || !valid()) {
        createFromData();
    }

    // Return buffer
    return m_buffer.get();
}

void Buffer::onDeinit()
{
    // Release buffer
    m_buffer.reset();
}

void Buffer::createFromData()
{
    // Create new buffer
    m_buffer = cppassist::make_unique<globjects::Buffer>();

    // Check buffer
    if (!m_buffer) {
        return;
    }

    // Set buffer data
    m_buffer->setData(m_data.size(), m_data.data(), gl::GL_STATIC_DRAW);

    // Flag buffer valid
    setValid(true);
}


} // namespace opengl
} // namespace rendercore
