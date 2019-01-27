
#include <rendercore/rendering/Drawable.h>

#include <cassert>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/enum.h>

#include <globjects/VertexArray.h>
#include <globjects/VertexAttributeBinding.h>


namespace rendercore
{


Drawable::Drawable()
: m_vao(cppassist::make_unique<globjects::VertexArray>())
, m_drawMode(DrawMode::Arrays)
, m_size(0)
, m_primitiveMode(gl::GL_TRIANGLES)
, m_indexBufferType(gl::GL_UNSIGNED_INT)
, m_indexBuffer(nullptr)
{
}

Drawable::~Drawable()
{
}

globjects::VertexArray * Drawable::vao() const
{
    return m_vao.get();
}

DrawMode Drawable::drawMode() const
{
    return m_drawMode;
}

void Drawable::setDrawMode(DrawMode drawMode)
{
    m_drawMode = drawMode;
}

void Drawable::draw() const
{
    draw(m_drawMode);
}

void Drawable::draw(DrawMode drawMode) const
{
    switch (drawMode)
    {
    case DrawMode::ElementsIndices:
    case DrawMode::ElementsIndexBuffer:
        drawElements();
        break;

    case DrawMode::Arrays:
    default:
        drawArrays();
        break;
    }
}

void Drawable::drawArrays() const
{
    drawArrays(m_primitiveMode, 0, m_size);
}

void Drawable::drawArrays(gl::GLenum mode) const
{
    drawArrays(mode, 0, m_size);
}

void Drawable::drawArrays(gl::GLint first, gl::GLsizei count) const
{
    drawArrays(m_primitiveMode, first, count);
}

void Drawable::drawArrays(gl::GLenum mode, gl::GLint first, gl::GLsizei count) const
{
    m_vao->drawArrays(mode, first, count);
}

void Drawable::drawElements() const
{
    drawElements(m_primitiveMode);
}

void Drawable::drawElements(gl::GLenum mode) const
{
    if (m_drawMode == DrawMode::ElementsIndices)
    {
        drawElements(mode, m_size, gl::GL_UNSIGNED_INT, m_indices.data());
    }
    else
    {
        drawElements(mode, m_size, m_indexBufferType, m_indexBuffer);
    }
}

void Drawable::drawElements(gl::GLenum mode, gl::GLsizei count, gl::GLenum type, const void * indices) const
{
    // [TODO]: rethink recorded vao state
    globjects::Buffer::unbind(gl::GL_ELEMENT_ARRAY_BUFFER);

    m_vao->drawElements(mode, count, type, indices);
}

void Drawable::drawElements(gl::GLenum mode, gl::GLsizei count, gl::GLenum type, globjects::Buffer *) const
{
    // [TODO]: rethink recorded vao state
    m_vao->drawElements(mode, count, type, nullptr);
}

gl::GLsizei Drawable::size() const
{
    return m_size;
}

void Drawable::setSize(gl::GLsizei size)
{
    m_size = size;
}

gl::GLenum Drawable::primitiveMode() const
{
    return m_primitiveMode;
}

void Drawable::setPrimitiveMode(gl::GLenum mode)
{
    m_primitiveMode = mode;
}

globjects::Buffer * Drawable::buffer(size_t index)
{
    if (m_buffers.count(index) == 0)
    {
        return nullptr;
    }

    return m_buffers.at(index);
}

globjects::Buffer * Drawable::buffer(size_t index) const
{
    if (m_buffers.count(index) == 0)
    {
        return nullptr;
    }

    return m_buffers.at(index);
}

void Drawable::setBuffer(size_t index, globjects::Buffer * buffer)
{
    m_buffers[index] = buffer;
}

globjects::Buffer * Drawable::indexBuffer() const
{
    return m_indexBuffer;
}

void Drawable::setIndexBuffer(globjects::Buffer * buffer)
{
    m_vao->bind();
    buffer->bind(gl::GL_ELEMENT_ARRAY_BUFFER);
    m_indexBuffer = buffer;
    m_vao->unbind();
}

void Drawable::setIndexBuffer(globjects::Buffer * buffer, gl::GLenum bufferType)
{
    setIndexBuffer(buffer);
    setIndexBufferType(bufferType);
}

gl::GLenum Drawable::indexBufferType() const
{
    return m_indexBufferType;
}

void Drawable::setIndexBufferType(gl::GLenum bufferType)
{
    m_indexBufferType = bufferType;
}

const std::vector<std::uint32_t> & Drawable::indices() const
{
    return m_indices;
}

void Drawable::setIndices(const std::vector<std::uint32_t> & indices)
{
    m_indices = indices;
}

globjects::VertexAttributeBinding * Drawable::attributeBinding(size_t index) const
{
    return m_vao->binding(index);
}

void Drawable::setAttributeBindingBuffer(size_t bindingIndex, size_t bufferIndex, gl::GLint baseOffset, gl::GLint stride)
{
    assert(m_buffers.count(bufferIndex) > 0);

    m_vao->binding(bindingIndex)->setBuffer(m_buffers.at(bufferIndex), baseOffset, stride);
}

void Drawable::setAttributeBindingFormat(size_t bindingIndex, gl::GLint size, gl::GLenum type, gl::GLboolean normalized, gl::GLuint relativeOffset)
{
    m_vao->binding(bindingIndex)->setFormat(size, type, normalized, relativeOffset);
}

void Drawable::setAttributeBindingFormatI(size_t bindingIndex, gl::GLint size, gl::GLenum type, gl::GLuint relativeOffset)
{
    m_vao->binding(bindingIndex)->setIFormat(size, type, relativeOffset);
}

void Drawable::setAttributeBindingFormatL(size_t bindingIndex, gl::GLint size, gl::GLenum type, gl::GLuint relativeOffset)
{
    m_vao->binding(bindingIndex)->setLFormat(size, type, relativeOffset);
}

void Drawable::bindAttribute(size_t bindingIndex, gl::GLint attributeIndex)
{
    m_vao->binding(bindingIndex)->setAttribute(attributeIndex);
}

void Drawable::bindAttributes(const std::vector<gl::GLint> & attributeIndices)
{
    for (size_t i = 0; i < attributeIndices.size(); ++i)
    {
        m_vao->binding(i)->setAttribute(attributeIndices.at(i));
    }
}

void Drawable::enableAttributeBinding(size_t bindingIndex)
{
    m_vao->enable(m_vao->binding(bindingIndex)->attributeIndex());
}

void Drawable::enableAllAttributeBindings()
{
    for (const globjects::VertexAttributeBinding * binding : m_vao->bindings())
    {
        m_vao->enable(binding->attributeIndex());
    }
}


} // namespace rendercore
