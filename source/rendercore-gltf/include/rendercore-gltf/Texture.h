
#pragma once


#include <string>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Texture
*/
class RENDERCORE_GLTF_API Texture
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Texture();

    /**
    *  @brief
    *    Destructor
    */
    ~Texture();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Name
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Set name
    *
    *  @param[in] name
    *    Name
    */
    void setName(const std::string & name);

    /**
    *  @brief
    *    Get sampler
    *
    *  @return
    *    Sampler index (-1 for none)
    */
    int sampler() const;

    /**
    *  @brief
    *    Set sampler
    *
    *  @param[in] sampler
    *    Sampler index (-1 for none)
    */
    void setSampler(int image);

    /**
    *  @brief
    *    Get image
    *
    *  @return
    *    Image index (-1 for none)
    */
    int image() const;

    /**
    *  @brief
    *    Set image
    *
    *  @param[in] image
    *    Image index (-1 for none)
    */
    void setImage(int image);

protected:
    std::string m_name;    ///< Name
    int         m_sampler; ///< Sampler index (-1 for none)
    int         m_image;   ///< Image index (-1 for none)
};


} // namespace gltf
} // namespace rendercore
