
#include <rendercore-gltf/Material.h>


namespace rendercore
{
namespace gltf
{


Material::Material()
: m_baseColorTexture(-1)
, m_baseColorFactor(1.0f, 1.0f, 1.0f, 1.0f)
, m_metallicRoughnessTexture(-1)
, m_metallicFactor(1.0f)
, m_roughnessFactor(1.0f)
, m_normalTexture(-1)
, m_occlusionTexture(-1)
, m_emissiveTexture(-1)
, m_emissiveFactor(0.0f, 0.0f, 0.0f)
, m_alphaMode("OPAQUE")
, m_alphaCutoff(0.5f)
, m_doubleSided(false)
{
}

Material::~Material()
{
}

const std::string & Material::name() const
{
    return m_name;
}

void Material::setName(const std::string & name)
{
    m_name = name;
}

int Material::baseColorTexture() const
{
    return m_baseColorTexture;
}

void Material::setBaseColorTexture(int index)
{
    m_baseColorTexture = index;
}

glm::vec4 Material::baseColorFactor() const
{
    return m_baseColorFactor;
}

void Material::setBaseColorFactor(const glm::vec4 & baseColorFactor)
{
    m_baseColorFactor = baseColorFactor;
}

int Material::metallicRoughnessTexture() const
{
    return m_metallicRoughnessTexture;
}

void Material::setMetallicRoughnessTexture(int index)
{
    m_metallicRoughnessTexture = index;
}

float Material::metallicFactor() const
{
    return m_metallicFactor;
}

void Material::setMetallicFactor(float metallicFactor)
{
    m_metallicFactor = metallicFactor;
}

float Material::roughnessFactor() const
{
    return m_roughnessFactor;
}

void Material::setRoughnessFactor(float roughnessFactor)
{
    m_roughnessFactor = roughnessFactor;
}

int Material::normalTexture() const
{
    return m_normalTexture;
}

void Material::setNormalTexture(int index)
{
    m_normalTexture = index;
}

int Material::occlusionTexture() const
{
    return m_occlusionTexture;
}

void Material::setOcclusionTexture(int index)
{
    m_occlusionTexture = index;
}

int Material::emissiveTexture() const
{
    return m_emissiveTexture;
}

void Material::setEmissiveTexture(int index)
{
    m_emissiveTexture = index;
}

glm::vec3 Material::emissiveFactor() const
{
    return m_emissiveFactor;
}

void Material::setEmissiveFactor(const glm::vec3 & emissive)
{
    m_emissiveFactor = emissive;
}

const std::string & Material::alphaMode() const
{
    return m_alphaMode;
}

void Material::setAlphaMode(const std::string & alphaMode)
{
    m_alphaMode = alphaMode;
}

float Material::alphaCutoff() const
{
    return m_alphaCutoff;
}

void Material::setAlphaCutoff(float alphaCutoff)
{
    m_alphaCutoff = alphaCutoff;
}

bool Material::doubleSided() const
{
    return m_doubleSided;
}

void Material::setDoubleSided(bool doubleSided)
{
    m_doubleSided = doubleSided;
}


} // namespace gltf
} // namespace rendercore
