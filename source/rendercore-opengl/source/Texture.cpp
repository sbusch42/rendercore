
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

    // Flag texture valid
    setValid(true);
}


} // namespace opengl
} // namespace rendercore
