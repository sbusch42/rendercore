
#include <rendercore-opengl/Primitive.h>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>

#include <globjects/VertexAttributeBinding.h>

#include <rendercore-opengl/Buffer.h>
#include <rendercore-opengl/VertexAttribute.h>


namespace rendercore
{
namespace opengl
{


Primitive::Primitive()
: m_mode(gl::GL_NONE)
, m_indexBuffer(nullptr)
, m_indexType(gl::GL_UNSIGNED_INT)
, m_numElements(0)
, m_material(0)
{
}

Primitive::~Primitive()
{
}

gl::GLenum Primitive::mode() const
{
    return m_mode;
}

void Primitive::setMode(gl::GLenum mode)
{
    m_mode = mode;
}

Buffer * Primitive::indexBuffer() const
{
    return m_indexBuffer;
}

gl::GLenum Primitive::indexBufferType() const
{
    return m_indexType;
}

void Primitive::setIndexBuffer(Buffer * buffer, gl::GLenum type)
{
    m_indexBuffer = buffer;
    m_indexType   = type;
}

unsigned int Primitive::numElements() const
{
    return m_numElements;
}

void Primitive::setNumElements(unsigned int numElements)
{
    m_numElements = numElements;
}

const std::unordered_map<size_t, const VertexAttribute *> & Primitive::attributeBindings() const
{
    return m_attributes;
}

const VertexAttribute * Primitive::attributeBinding(size_t index) const
{
    if (index >= m_attributes.size()) {
        return nullptr;
    }

    return m_attributes.at(index);
}

void Primitive::bindAttribute(size_t index, const VertexAttribute * vertexAttribute)
{
    m_attributes[index] = vertexAttribute;
}

unsigned int Primitive::material() const
{
    return m_material;
}

void Primitive::setMaterial(unsigned int material)
{
    m_material = material;
}

void Primitive::draw()
{
    // Check if VAO needs to be created
    if (!m_vao.get()) {
        prepareVAO();
    }

    // Bind VAO
    m_vao->bind();

    // Draw with index buffer (DrawElements)
    if (m_indexBuffer) {
        m_indexBuffer->buffer()->bind(gl::GL_ELEMENT_ARRAY_BUFFER);
        m_vao->drawElements(m_mode, m_numElements, m_indexType, nullptr);
    }

    // Draw without buffer (DrawArrays)
    else {
        globjects::Buffer::unbind(gl::GL_ELEMENT_ARRAY_BUFFER);
        m_vao->drawArrays(m_mode, 0, m_numElements);
    }

    // Release VAO
    m_vao->unbind();
}

void Primitive::deinit()
{
    // Release VAO
    m_vao.reset();
}

void Primitive::prepareVAO()
{
    // Create VAO
    m_vao = cppassist::make_unique<globjects::VertexArray>();

    // Bind VAO
    m_vao->bind();

    // Bind vertex attributes
    size_t i = 0;
    for (auto it : m_attributes) {
        // Get attribute index and VertexAttribute
        size_t index = it.first;
        auto * attr  = it.second;

        // Configure vertex attribute
        m_vao->enable(index);
        m_vao->binding(i)->setAttribute(index);
        m_vao->binding(i)->setBuffer(attr->buffer()->buffer(), attr->baseOffset(), attr->stride());
        m_vao->binding(i)->setFormat(attr->components(), attr->type(), attr->normalize(), attr->relativeOffset());

        // Next
        i++;
    }

    // Release VAO
    m_vao->unbind();
}


} // namespace opengl
} // namespace rendercore
