
#pragma once


#include <string>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Texture sampler
*/
class RENDERCORE_GLTF_API Sampler
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Sampler();

    /**
    *  @brief
    *    Destructor
    */
    ~Sampler();

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
    *    Get minification filter
    *
    *  @return
    *    Minification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    unsigned int minFilter() const;

    /**
    *  @brief
    *    Set minification filter
    *
    *  @param[in] filter
    *    Minification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    void setMinFilter(unsigned int filter);

    /**
    *  @brief
    *    Get magnification filter
    *
    *  @return
    *    Magnification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    unsigned int magFilter() const;

    /**
    *  @brief
    *    Set magnification filter
    *
    *  @param[in] filter
    *    Magnification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    void setMagFilter(unsigned int filter);

    /**
    *  @brief
    *    Get wrapping mode (S)
    *
    *  @return
    *    Wrapping mode (OpenGL enum, e.g., GL_NEAREST)
    */
    unsigned int wrapS() const;

    /**
    *  @brief
    *    Set wrapping filter (S)
    *
    *  @param[in] mode
    *    Magnification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    void setWrapS(unsigned int mode);

    /**
    *  @brief
    *    Get wrapping mode (T)
    *
    *  @return
    *    Wrapping mode (OpenGL enum, e.g., GL_NEAREST)
    */
    unsigned int wrapT() const;

    /**
    *  @brief
    *    Set wrapping filter (T)
    *
    *  @param[in] mode
    *    Magnification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    void setWrapT(unsigned int mode);

protected:
    std::string m_name;       ///< Name
    unsigned int m_minFilter; ///< Minification filter (OpenGL enum, e.g., GL_NEAREST)
    unsigned int m_magFilter; ///< Magnification filter (OpenGL enum, e.g., GL_NEAREST)
    unsigned int m_wrapS;     ///< Wrapping mode (OpenGL enum, e.g., GL_NEAREST)
    unsigned int m_wrapT;     ///< Wrapping mode (OpenGL enum, e.g., GL_NEAREST)
};


} // namespace gltf
} // namespace rendercore
