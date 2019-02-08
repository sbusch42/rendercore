
#include <rendercore-opengl/Geometry2.h>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>


namespace rendercore
{
namespace opengl
{


Geometry2::Geometry2(GpuContainer * container)
: GpuContainer(container)
{
}

Geometry2::~Geometry2()
{
}

const std::vector< Buffer * > & Geometry2::buffers() const
{
    // Return list of buffers
    return m_buffers;
}

const Buffer * Geometry2::buffer(size_t index) const
{
    // Check if index is valid
    if (index >= m_buffers.size()) {
        return nullptr;
    }

    // Return buffer
    return m_buffers[index];
}

Buffer * Geometry2::buffer(size_t index)
{
    // Check if index is valid
    if (index >= m_buffers.size()) {
        return nullptr;
    }

    // Return buffer
    return m_buffers[index];
}

void Geometry2::addBuffer(Buffer * buffer)
{
    // Check if buffer is not empty
    if (!buffer) {
        return;
    }

    // Add buffer to geometry
    m_buffers.push_back(buffer);
}

void Geometry2::addBuffer(std::unique_ptr<Buffer> && buffer)
{
    // Add buffer
    addBuffer(buffer.get());

    // Transfer ownership of buffer
    m_ownbuffers.push_back(std::move(buffer));
}

Buffer * Geometry2::createBuffer(const void * data, unsigned int size)
{
    // Create new buffer
    auto buffer = cppassist::make_unique<Buffer>(this);

    // Set buffer data
    buffer->setData(data, size);

    // Add buffer
    auto * bufferPtr = buffer.get();
    addBuffer(std::move(buffer));

    // Return buffer
    return bufferPtr;
}

const std::vector< std::unique_ptr<VertexAttribute> > & Geometry2::vertexAttributes() const
{
    // Return list of vertex attributes
    return m_vertexAttributes;
}

VertexAttribute * Geometry2::addVertexAttribute(Buffer * buffer
, unsigned int baseOffset
, unsigned int relativeOffset
, int stride
, gl::GLenum type
, unsigned int components
, bool normalize)
{
    // Create vertex attribute
    auto vertexAttribute = cppassist::make_unique<VertexAttribute>(
        buffer,
        baseOffset,
        relativeOffset,
        stride,
        type,
        components,
        normalize
    );

    // Add vertex attribute
    auto * vertexAttributePtr = vertexAttribute.get();
    m_vertexAttributes.push_back(std::move(vertexAttribute));

    // Return vertex attribute
    return vertexAttributePtr;
}

const std::vector< std::unique_ptr<Primitive> > & Geometry2::primitives() const
{
    // Return list of primitives
    return m_primitives;
}

const Primitive * Geometry2::primitive(size_t index) const
{
    // Check if index is valid
    if (index >= m_primitives.size()) {
        return nullptr;
    }

    // Return primitive
    return m_primitives[index].get();
}

void Geometry2::addPrimitive(std::unique_ptr<Primitive> && primitive)
{
    // Add primitive
    m_primitives.push_back(std::move(primitive));
}

void Geometry2::draw() const
{
    // Draw primitives
    for (auto & primitive : m_primitives) {
        primitive->draw();
    }
}

void Geometry2::onDeinit()
{
    // Release GPU-data
    for (auto & primitive : m_primitives) {
        primitive->deinit();
    }
}


} // namespace opengl
} // namespace rendercore
