
#include <rendercore-gltf/Image.h>


namespace rendercore
{
namespace gltf
{


Image::Image()
: m_bufferView(-1)
{
}

Image::~Image()
{
}

const std::string & Image::name() const
{
    return m_name;
}

void Image::setName(const std::string & name)
{
    m_name = name;
}

const std::string & Image::uri() const
{
    return m_uri;
}

void Image::setURI(const std::string & uri)
{
    m_uri = uri;
}

const std::string & Image::mimeType() const
{
    return m_mimeType;
}

void Image::setMimeType(const std::string & mimeType)
{
    m_mimeType = mimeType;
}

int Image::bufferView() const
{
    return m_bufferView;
}

void Image::setBufferView(int bufferView)
{
    m_bufferView = bufferView;
}


} // namespace gltf
} // namespace rendercore
