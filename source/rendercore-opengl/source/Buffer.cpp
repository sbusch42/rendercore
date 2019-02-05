
#include <rendercore-opengl/Buffer.h>

#include <algorithm>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>
#include <glbinding/gl/enum.h>


namespace rendercore
{
namespace opengl
{


Buffer::Buffer(GpuObject * parent)
: GpuObject(parent)
{
}

Buffer::~Buffer()
{
}

const globjects::Buffer * Buffer::buffer() const
{
    return m_buffer.get();
}

globjects::Buffer * Buffer::buffer()
{
    return m_buffer.get();
}

unsigned int Buffer::size() const
{
    return m_data.size();
}

void Buffer::allocate(unsigned int size)
{
    // Clear old data
    m_data.clear();

    // Set new size
    m_data.resize(size);
}

const char * Buffer::data() const
{
    return m_data.data();
}

char * Buffer::data()
{
    return m_data.data();
}

void Buffer::setData(char * data, unsigned int size)
{
    // Clear old data
    m_data.clear();

    // Check if data is valid
    if (data && size > 0) {
        // Allocate data
        m_data.resize(size);

        // Copy data
        std::copy_n(data, size, m_data.data());
    }
}

void Buffer::onContextInit(AbstractContext *)
{
    // If buffer was lost, try to restore it from data
    if (!m_buffer.get()) {
        createFromData();
    }
}

void Buffer::onContextDeinit(AbstractContext *)
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
}


} // namespace opengl
} // namespace rendercore
