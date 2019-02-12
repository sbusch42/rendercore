
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
class RENDERCORE_GLTF_API Image
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Image();

    /**
    *  @brief
    *    Destructor
    */
    ~Image();

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
    *    Get uri
    *
    *  @return
    *    URI
    */
    const std::string & uri() const;

    /**
    *  @brief
    *    Set uri
    *
    *  @param[in] uri
    *    URI
    */
    void setURI(const std::string & uri);

    /**
    *  @brief
    *    Get mime type
    *
    *  @return
    *    Mime type
    */
    const std::string & mimeType() const;

    /**
    *  @brief
    *    Set mime type
    *
    *  @param[in] mimeType
    *    Mime type
    */
    void setMimeType(const std::string & mimeType);

    /**
    *  @brief
    *    Get buffer view
    *
    *  @return
    *    Buffer view index (-1 for none)
    */
    int bufferView() const;

    /**
    *  @brief
    *    Set buffer view
    *
    *  @param[in] bufferView
    *    Buffer view index (-1 for none)
    */
    void setBufferView(int bufferView);

protected:
    std::string m_name;       ///< Name
    std::string m_uri;        ///< URI
    std::string m_mimeType;   ///< Mime type
    int         m_bufferView; ///< Buffer view index (-1 for none)
};


} // namespace gltf
} // namespace rendercore
