
#pragma once


#include <string>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Buffer
*/
class RENDERCORE_GLTF_API Buffer
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Buffer();

    /**
    *  @brief
    *    Destructor
    */
    ~Buffer();

    /**
    *  @brief
    *    Get buffer size
    *
    *  @return
    *    Size of buffer (in bytes)
    */
    int size() const;

    /**
    *  @brief
    *    Set buffer size
    *
    *  @param[in] size
    *    Size of buffer (in bytes)
    */
    void setSize(int size);

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
    void setUri(const std::string & uri);

protected:
    unsigned int m_size; ///< Buffer size (in bytes)
    std::string  m_uri;  ///< URI
};


} // namespace gltf
} // namespace rendercore
