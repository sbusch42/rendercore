
#pragma once


#include <memory>

#include <glbinding/gl/gl.h>

#include <globjects/Texture.h>

#include <rendercore/GpuObject.h>
#include <rendercore/Image.h>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Texture
*/
class RENDERCORE_OPENGL_API Texture : public rendercore::GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    Texture(GpuContainer * container = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Texture();

    /**
    *  @brief
    *    Get image
    *
    *  @return
    *    Image that is the source for the texture (can be null)
    */
    const rendercore::Image * image() const;

    /**
    *  @brief
    *    Get image
    *
    *  @return
    *    Image that is the source for the texture (can be null)
    */
    rendercore::Image * image();

    /**
    *  @brief
    *    Set image
    *
    *  @param[in] image
    *    Image that is the source for the texture (can be null)
    *
    *  @remarks
    *    If an image is set as the source for a texture, it will
    *    be used to immediately create the texture. It will also
    *    be used as the source of information to restore the
    *    texture data when needed (e.g., after a context switch).
    */
    void setImage(std::unique_ptr<rendercore::Image> image);

    /**
    *  @brief
    *    Load texture from .glraw file
    *
    *  @param[in] filename
    *    Path to texture file
    *
    *  @remarks
    *    This function will load the given file and set it as
    *    the image source for this texture (see setImage).
    */
    void load(const std::string & filename);

    /**
    *  @brief
    *    Get minification filter
    *
    *  @return
    *    Minification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    gl::GLenum minFilter() const;

    /**
    *  @brief
    *    Set minification filter
    *
    *  @param[in] filter
    *    Minification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    void setMinFilter(gl::GLenum filter);

    /**
    *  @brief
    *    Get magnification filter
    *
    *  @return
    *    Magnification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    gl::GLenum magFilter() const;

    /**
    *  @brief
    *    Set magnification filter
    *
    *  @param[in] filter
    *    Magnification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    void setMagFilter(gl::GLenum filter);

    /**
    *  @brief
    *    Get wrapping mode (S)
    *
    *  @return
    *    Wrapping mode (OpenGL enum, e.g., GL_NEAREST)
    */
    gl::GLenum wrapS() const;

    /**
    *  @brief
    *    Set wrapping filter (S)
    *
    *  @param[in] mode
    *    Magnification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    void setWrapS(gl::GLenum mode);

    /**
    *  @brief
    *    Get wrapping mode (T)
    *
    *  @return
    *    Wrapping mode (OpenGL enum, e.g., GL_NEAREST)
    */
    gl::GLenum wrapT() const;

    /**
    *  @brief
    *    Set wrapping filter (T)
    *
    *  @param[in] mode
    *    Magnification filter (OpenGL enum, e.g., GL_NEAREST)
    */
    void setWrapT(gl::GLenum mode);

    /**
    *  @brief
    *    Get OpenGL texture
    *
    *  @return
    *    OpenGL texture (can be null)
    *
    *  @notes
    *    - Requires an active rendering context
    */
    globjects::Texture * texture();

    // [TODO]

protected:
    // Virtual GpuObject functions
    virtual void onDeinit() override;

    /**
    *  @brief
    *    Create texture from image
    *
    *  @notes
    *    - Requires an active rendering context
    */
    void createFromImage();

protected:
    gl::GLenum m_minFilter; ///< Minification filter
    gl::GLenum m_magFilter; ///< Magnification filter
    gl::GLenum m_wrapS;     ///< Wrapping mode
    gl::GLenum m_wrapT;     ///< Wrapping mode

    std::unique_ptr<globjects::Texture> m_texture; ///< OpenGL texture (can be null)
    std::unique_ptr<rendercore::Image>  m_image;   ///< Image that is the source for the texture (can be null)
};


} // namespace opengl
} // namespace rendercore
