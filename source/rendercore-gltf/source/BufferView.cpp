
#include <rendercore-gltf/BufferView.h>


namespace rendercore
{
namespace gltf
{


BufferView::BufferView()
: m_buffer(0)
, m_size(0)
, m_offset(0)
, m_stride(0)
, m_target(0)
{
}

BufferView::~BufferView()
{
}

unsigned int BufferView::buffer() const
{
    return m_buffer;
}

void BufferView::setBuffer(unsigned int buffer)
{
    m_buffer = buffer;
}

unsigned int BufferView::size() const
{
    return m_size;
}

void BufferView::setSize(unsigned int size)
{
    m_size = size;
}

unsigned int BufferView::offset() const
{
    return m_offset;
}

void BufferView::setOffset(unsigned int offset)
{
    m_offset = offset;
}

unsigned int BufferView::stride() const
{
    return m_stride;
}

void BufferView::setStride(unsigned int stride)
{
    m_stride = stride;
}

unsigned int BufferView::target() const
{
    return m_target;
}

void BufferView::setTarget(unsigned int target)
{
    m_target = target;
}


} // namespace gltf
} // namespace rendercore
