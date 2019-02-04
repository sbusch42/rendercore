
#include <rendercore-gltf/Primitive.h>


namespace rendercore
{
namespace gltf
{


Primitive::Primitive()
: m_mode(0)
, m_material(0)
, m_indices(-1)
{
}

Primitive::~Primitive()
{
}

unsigned int Primitive::mode() const
{
    return m_mode;
}

void Primitive::setMode(unsigned int mode)
{
    m_mode = mode;
}

unsigned int Primitive::material() const
{
    return m_material;
}

void Primitive::setMaterial(unsigned int material)
{
    m_material = material;
}

int Primitive::indices() const
{
    return m_indices;
}

void Primitive::setIndices(int indices)
{
    m_indices = indices;
}

std::map<std::string, unsigned int> Primitive::attributes() const
{
    return m_attributes;
}

void Primitive::setAttributes(const std::map<std::string, unsigned int> & attributes)
{
    m_attributes = attributes;
}


} // namespace gltf
} // namespace rendercore
