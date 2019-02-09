
#pragma once


#include <string>

#include <glm/glm.hpp>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Material
*/
class RENDERCORE_GLTF_API Material
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Material();

    /**
    *  @brief
    *    Destructor
    */
    ~Material();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Material name
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Set name
    *
    *  @param[in] name
    *    Material name
    */
    void setName(const std::string & name);

    /**
    *  @brief
    *    Get base color texture
    *
    *  @return
    *    Filename of base color texture
    */
    const std::string & baseColorTexture() const;

    /**
    *  @brief
    *    Set base color texture
    *
    *  @param[in] filename
    *    Filename of base color texture
    */
    void setBaseColorTexture(const std::string & filename);

    /**
    *  @brief
    *    Get base color factor
    *
    *  @return
    *    Base color factor
    */
    glm::vec4 baseColorFactor() const;

    /**
    *  @brief
    *    Set base color factor
    *
    *  @param[in] baseColorFactor
    *    Base color factor
    */
    void setBaseColorFactor(const glm::vec4 & baseColorFactor);

    /**
    *  @brief
    *    Get metallic-roughness texture
    *
    *  @return
    *    Filename of metallic-roughness texture
    */
    const std::string & metallicRoughnessTexture() const;

    /**
    *  @brief
    *    Set metallic-roughness texture
    *
    *  @param[in] filename
    *    Filename of metallic-roughness texture
    */
    void setMetallicRoughnessTexture(const std::string & filename);

    /**
    *  @brief
    *    Get metalness factor
    *
    *  @return
    *    Metalness of the material
    */
    float metallicFactor() const;

    /**
    *  @brief
    *    Set metalness factor
    *
    *  @param[in] metallicFactor
    *    Metalness of the material
    */
    void setMetallicFactor(float metallicFactor);

    /**
    *  @brief
    *    Get roughness factor
    *
    *  @return
    *    Roughness of the material
    */
    float roughnessFactor() const;

    /**
    *  @brief
    *    Set roughness factor
    *
    *  @param[in] roughnessFactor
    *    Roughness of the material
    */
    void setRoughnessFactor(float roughnessFactor);

    /**
    *  @brief
    *    Get normal texture
    *
    *  @return
    *    Filename of normal texture
    */
    const std::string & normalTexture() const;

    /**
    *  @brief
    *    Set normal texture
    *
    *  @param[in] filename
    *    Filename of normal texture
    */
    void setNormalTexture(const std::string & filename);

    /**
    *  @brief
    *    Get occlusion texture
    *
    *  @return
    *    Filename of occlusion texture
    */
    const std::string & occlusionTexture() const;

    /**
    *  @brief
    *    Set occlusion texture
    *
    *  @param[in] filename
    *    Filename of occlusion texture
    */
    void setOcclusionTexture(const std::string & filename);

    /**
    *  @brief
    *    Get emissive texture
    *
    *  @return
    *    Filename of emissive texture
    */
    const std::string & emissiveTexture() const;

    /**
    *  @brief
    *    Set emissive texture
    *
    *  @param[in] filename
    *    Filename of emissive texture
    */
    void setEmissiveTexture(const std::string & filename);

    /**
    *  @brief
    *    Get emissive factor
    *
    *  @return
    *    Emissive color of the material
    */
    glm::vec3 emissiveFactor() const;

    /**
    *  @brief
    *    Set emissive factor
    *
    *  @param[in] emissive
    *    Emissive color of the material
    */
    void setEmissiveFactor(const glm::vec3 & emissive);

    /**
    *  @brief
    *    Get alpha mode
    *
    *  @return
    *    Alpha mode
    */
    const std::string & alphaMode() const;

    /**
    *  @brief
    *    Set alpha mode
    *
    *  @param[in] alphaMode
    *    Alpha mode
    */
    void setAlphaMode(const std::string & alphaMode);

    /**
    *  @brief
    *    Get alpha cutoff
    *
    *  @return
    *    Alpha cutoff value
    */
    float alphaCutoff() const;

    /**
    *  @brief
    *    Set alpha cutoff
    *
    *  @param[in] alphaCutoff
    *    Alpha cutoff value
    */
    void setAlphaCutoff(float alphaCutoff);

    /**
    *  @brief
    *    Get double-sided
    *
    *  @return
    *    Specifies whether the material is double sided
    */
    bool doubleSided() const;

    /**
    *  @brief
    *    Set double-sided
    *
    *  @param[in] doubleSided
    *    Specifies whether the material is double sided
    */
    void setDoubleSided(bool doubleSided);

protected:
    std::string m_name;                     ///< Material name
    std::string m_baseColorTexture;         ///< Filename of base color texture
    glm::vec4   m_baseColorFactor;          ///< Base color factor
    std::string m_metallicRoughnessTexture; ///< Filename of metallic-roughness texture
    float       m_metallicFactor;           ///< Metalness of the material
    float       m_roughnessFactor;          ///< Roughness of the material
    std::string m_normalTexture;            ///< Filename of normal texture
    std::string m_occlusionTexture;         ///< Filename of occlusion texture
    std::string m_emissiveTexture;          ///< Filename of emissive texture
    glm::vec3   m_emissiveFactor;           ///< Emissive color of the material
    std::string m_alphaMode;                ///< Alpha mode
    float       m_alphaCutoff;              ///< Alpha cutoff value
    bool        m_doubleSided;              ///< Specifies whether the material is double sided
};


} // namespace gltf
} // namespace rendercore
