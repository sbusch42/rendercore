
#include <rendercore-opengl/Texture.h>

#include <glbinding/gl/gl.h>
#include <glbinding/gl/enum.h>

#include <rendercore/ImageLoader.h>
#include <rendercore/Image.h>


namespace rendercore
{
namespace opengl
{


Texture::Texture(GpuContainer * container)
: GpuObject(container)
, m_minFilter(gl::GL_LINEAR)
, m_magFilter(gl::GL_LINEAR)
, m_wrapS(gl::GL_CLAMP_TO_EDGE)
, m_wrapT(gl::GL_CLAMP_TO_EDGE)
{
}

Texture::~Texture()
{
}

const rendercore::Image * Texture::image() const
{
    return m_image.get();
}

rendercore::Image * Texture::image()
{
    return m_image.get();
}

void Texture::setImage(std::unique_ptr<rendercore::Image> image)
{
    // Store image
    m_image = std::move(image);

    // Flag texture invalid
    setValid(false);
}

void Texture::load(const std::string & filename)
{
    // Load image
    ImageLoader loader;
    setImage(loader.load(filename));
}

gl::GLenum Texture::minFilter() const
{
    return m_minFilter;
}

void Texture::setMinFilter(gl::GLenum filter)
{
    m_minFilter = filter;
}

gl::GLenum Texture::magFilter() const
{
    return m_magFilter;
}

void Texture::setMagFilter(gl::GLenum filter)
{
    m_magFilter = filter;
}

gl::GLenum Texture::wrapS() const
{
    return m_wrapS;
}

void Texture::setWrapS(gl::GLenum filter)
{
    m_wrapS = filter;
}

gl::GLenum Texture::wrapT() const
{
    return m_wrapT;
}

void Texture::setWrapT(gl::GLenum filter)
{
    m_wrapT = filter;
}

globjects::Texture * Texture::texture()
{
    // Check if texture needs to be updated or restored
    if (!m_texture.get() || !valid()) {
        createFromImage();
    }

    // Return texture
    return m_texture.get();
}

void Texture::onDeinit()
{
    // Release texture
    m_texture.reset();
}

void Texture::createFromImage()
{
    // Create new texture
    m_texture = globjects::Texture::createDefault(gl::GL_TEXTURE_2D);

    // Check image
    if (!m_image) {
        return;
    }

    // Create texture
    m_texture->image2D(
        0,
        gl::GL_RGBA8,
        m_image->width(),
        m_image->height(),
        0,
        static_cast<gl::GLenum>(m_image->format()),
        static_cast<gl::GLenum>(m_image->dataType()),
        m_image->data()
    );

    // Set texture parameters
    m_texture->setParameter(gl::GL_TEXTURE_MIN_FILTER, m_minFilter);
    m_texture->setParameter(gl::GL_TEXTURE_MAG_FILTER, m_magFilter);
    m_texture->setParameter(gl::GL_TEXTURE_WRAP_S,     m_wrapS);
    m_texture->setParameter(gl::GL_TEXTURE_WRAP_T,     m_wrapT);

    // Flag texture valid
    setValid(true);
}


} // namespace opengl
} // namespace rendercore
