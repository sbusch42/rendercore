
#include <rendercore-opengl/VertexAttribute.h>


namespace rendercore
{
namespace opengl
{


VertexAttribute::VertexAttribute(
    Buffer * buffer
  , unsigned int baseOffset
  , unsigned int relativeOffset
  , int stride
  , gl::GLenum type
  , unsigned int components
  , bool normalize)
: m_buffer(buffer)
, m_baseOffset(baseOffset)
, m_relativeOffset(relativeOffset)
, m_stride(stride)
, m_type(type)
, m_components(components)
, m_normalize(normalize)
{
}

VertexAttribute::~VertexAttribute()
{
}

Buffer * VertexAttribute::buffer() const
{
    return m_buffer;
}

unsigned int VertexAttribute::baseOffset() const
{
    return m_baseOffset;
}

unsigned int VertexAttribute::relativeOffset() const
{
    return m_relativeOffset;
}

unsigned int VertexAttribute::stride() const
{
    return m_stride;
}

gl::GLenum VertexAttribute::type() const
{
    return m_type;
}

unsigned int VertexAttribute::components() const
{
    return m_components;
}

bool VertexAttribute::normalize() const
{
    return m_normalize;
}


} // namespace opengl
} // namespace rendercore
