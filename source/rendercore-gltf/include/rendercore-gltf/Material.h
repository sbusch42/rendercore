
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
    *    Index of base color texture info (-1 for none)
    */
    int baseColorTexture() const;

    /**
    *  @brief
    *    Set base color texture
    *
    *  @param[in] index
    *    Index of base color texture info (-1 for none)
    */
    void setBaseColorTexture(int index);

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
    *    Index of metallic-roughness texture info (-1 for none)
    */
    int metallicRoughnessTexture() const;

    /**
    *  @brief
    *    Set metallic-roughness texture
    *
    *  @param[in] index
    *    Index of metallic-roughness texture info (-1 for none)
    */
    void setMetallicRoughnessTexture(int index);

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
    *    Index of normal texture info (-1 for none)
    */
    int normalTexture() const;

    /**
    *  @brief
    *    Set normal texture
    *
    *  @param[in] index
    *    Index of normal texture info (-1 for none)
    */
    void setNormalTexture(int index);

    /**
    *  @brief
    *    Get occlusion texture
    *
    *  @return
    *    Index of occlusion texture info (-1 for none)
    */
    int occlusionTexture() const;

    /**
    *  @brief
    *    Set occlusion texture
    *
    *  @param[in] index
    *    Index of occlusion texture info (-1 for none)
    */
    void setOcclusionTexture(int index);

    /**
    *  @brief
    *    Get emissive texture
    *
    *  @return
    *    Index of emissive texture info (-1 for none)
    */
    int emissiveTexture() const;

    /**
    *  @brief
    *    Set emissive texture
    *
    *  @param[in] index
    *    Index of emissive texture info (-1 for none)
    */
    void setEmissiveTexture(int index);

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
    int         m_baseColorTexture;         ///< Filename of base color texture
    glm::vec4   m_baseColorFactor;          ///< Base color factor
    int         m_metallicRoughnessTexture; ///< Filename of metallic-roughness texture
    float       m_metallicFactor;           ///< Metalness of the material
    float       m_roughnessFactor;          ///< Roughness of the material
    int         m_normalTexture;            ///< Filename of normal texture
    int         m_occlusionTexture;         ///< Filename of occlusion texture
    int         m_emissiveTexture;          ///< Filename of emissive texture
    glm::vec3   m_emissiveFactor;           ///< Emissive color of the material
    std::string m_alphaMode;                ///< Alpha mode
    float       m_alphaCutoff;              ///< Alpha cutoff value
    bool        m_doubleSided;              ///< Specifies whether the material is double sided
};


} // namespace gltf
} // namespace rendercore
