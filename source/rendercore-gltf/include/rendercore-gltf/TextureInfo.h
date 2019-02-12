
#pragma once


#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Texture info
*/
class RENDERCORE_GLTF_API TextureInfo
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TextureInfo();

    /**
    *  @brief
    *    Destructor
    */
    ~TextureInfo();

    /**
    *  @brief
    *    Get texture
    *
    *  @return
    *    Texture index
    */
    unsigned int texture() const;

    /**
    *  @brief
    *    Set texture
    *
    *  @param[in] texture
    *    Texture index
    */
    void setTexture(unsigned int texture);

    /**
    *  @brief
    *    Get UV index
    *
    *  @return
    *    Index of used UV set
    */
    unsigned int uvSet() const;

    /**
    *  @brief
    *    Set UV index
    *
    *  @param[in] index
    *    Index of used UV set
    */
    void setUVSet(unsigned int index);

    /**
    *  @brief
    *    Get normal scale
    *
    *  @return
    *    Scalar multiplier for normals
    */
    float scale() const;

    /**
    *  @brief
    *    Set normal scale
    *
    *  @param[in] scale
    *    Scalar multiplier for normals
    */
    void setScale(float scale);

    /**
    *  @brief
    *    Get occlusion strength
    *
    *  @return
    *    Scalar multiplier for occlusion
    */
    float strength() const;

    /**
    *  @brief
    *    Set occlusion strength
    *
    *  @param[in] strength
    *    Scalar multiplier for occlusion
    */
    void setStrength(float strength);

protected:
    unsigned int m_texture;  ///< Texture index
    unsigned int m_uvSet;    ///< Index of used UV set
    float        m_scale;    ///< Scalar multiplier for normals
    float        m_strength; ///< Scalar multiplier for occlusion
};


} // namespace gltf
} // namespace rendercore
