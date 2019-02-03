
#include <rendercore-opengl/Texture.h>

#include <glbinding/gl/gl.h>
#include <glbinding/gl/enum.h>

#include <rendercore/ImageLoader.h>
#include <rendercore/Image.h>


namespace rendercore
{
namespace opengl
{


Texture::Texture(GpuObject * parent)
: GpuObject(parent)
{
}

Texture::~Texture()
{
}

const globjects::Texture * Texture::texture() const
{
    return m_texture.get();
}

globjects::Texture * Texture::texture()
{
    return m_texture.get();
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

    // Do not create the texture right away, as there
    // might be currently no rendering context active.
    // The texture will be created in onContextInit().
}

void Texture::load(const std::string & filename)
{
    // Load image
    ImageLoader loader;
    setImage(loader.load(filename));
}

void Texture::onContextInit(AbstractContext *)
{
    // If texture was lost, try to restore it from image
    if (!m_texture.get()) {
        createFromImage();
    }
}

void Texture::onContextDeinit(AbstractContext *)
{
    // Make texture invalid
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
}


} // namespace opengl
} // namespace rendercore
