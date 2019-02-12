
#include <rendercore-gltf/TextureInfo.h>


namespace rendercore
{
namespace gltf
{


TextureInfo::TextureInfo()
: m_texture(0)
, m_uvSet(0)
, m_scale(1.0f)
, m_strength(1.0f)
{
}

TextureInfo::~TextureInfo()
{
}

unsigned int TextureInfo::texture() const
{
    return m_texture;
}

void TextureInfo::setTexture(unsigned int texture)
{
    m_texture = texture;
}

unsigned int TextureInfo::uvSet() const
{
    return m_uvSet;
}

void TextureInfo::setUVSet(unsigned int index)
{
    m_uvSet = index;
}

float TextureInfo::scale() const
{
    return m_scale;
}

void TextureInfo::setScale(float scale)
{
    m_scale = scale;
}

float TextureInfo::strength() const
{
    return m_strength;
}

void TextureInfo::setStrength(float strength)
{
    m_strength = strength;
}


} // namespace gltf
} // namespace rendercore
