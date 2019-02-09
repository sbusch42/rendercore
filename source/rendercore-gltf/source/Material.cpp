
#include <rendercore-gltf/Material.h>


namespace rendercore
{
namespace gltf
{


Material::Material()
: m_baseColorFactor(1.0f, 1.0f, 1.0f, 1.0f)
, m_metallicFactor(1.0f)
, m_roughnessFactor(1.0f)
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

const std::string & Material::baseColorTexture() const
{
    return m_baseColorTexture;
}

void Material::setBaseColorTexture(const std::string & filename)
{
    m_baseColorTexture = filename;
}

glm::vec4 Material::baseColorFactor() const
{
    return m_baseColorFactor;
}

void Material::setBaseColorFactor(const glm::vec4 & baseColorFactor)
{
    m_baseColorFactor = baseColorFactor;
}

const std::string & Material::metallicRoughnessTexture() const
{
    return m_metallicRoughnessTexture;
}

void Material::setMetallicRoughnessTexture(const std::string & filename)
{
    m_metallicRoughnessTexture = filename;
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

const std::string & Material::normalTexture() const
{
    return m_normalTexture;
}

void Material::setNormalTexture(const std::string & filename)
{
    m_normalTexture = filename;
}

const std::string & Material::occlusionTexture() const
{
    return m_occlusionTexture;
}

void Material::setOcclusionTexture(const std::string & filename)
{
    m_occlusionTexture = filename;
}

const std::string & Material::emissiveTexture() const
{
    return m_emissiveTexture;
}

void Material::setEmissiveTexture(const std::string & filename)
{
    m_emissiveTexture = filename;
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
