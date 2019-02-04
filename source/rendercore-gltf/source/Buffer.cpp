
#include <rendercore-gltf/Buffer.h>


namespace rendercore
{
namespace gltf
{


Buffer::Buffer()
: m_size(0)
{
}

Buffer::~Buffer()
{
}

int Buffer::size() const
{
    return m_size;
}

void Buffer::setSize(int size)
{
    m_size = size;
}

const std::string & Buffer::uri() const
{
    return m_uri;
}

void Buffer::setUri(const std::string & uri)
{
    m_uri = uri;
}


} // namespace gltf
} // namespace rendercore
