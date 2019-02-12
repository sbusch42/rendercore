
#include <rendercore-gltf/Texture.h>


namespace rendercore
{
namespace gltf
{


Texture::Texture()
: m_sampler(-1)
, m_image(-1)
{
}

Texture::~Texture()
{
}

const std::string & Texture::name() const
{
    return m_name;
}

void Texture::setName(const std::string & name)
{
    m_name = name;
}

int Texture::sampler() const
{
    return m_sampler;
}

void Texture::setSampler(int sampler)
{
    m_sampler = sampler;
}

int Texture::image() const
{
    return m_image;
}

void Texture::setImage(int image)
{
    m_image = image;
}


} // namespace gltf
} // namespace rendercore
