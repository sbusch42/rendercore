
#include <rendercore-opengl/Mesh.h>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>


namespace rendercore
{
namespace opengl
{


Mesh::Mesh(GpuContainer * container)
: GpuContainer(container)
{
}

Mesh::~Mesh()
{
}

const std::vector< Buffer * > & Mesh::buffers() const
{
    // Return list of buffers
    return m_buffers;
}

const Buffer * Mesh::buffer(size_t index) const
{
    // Check if index is valid
    if (index >= m_buffers.size()) {
        return nullptr;
    }

    // Return buffer
    return m_buffers[index];
}

Buffer * Mesh::buffer(size_t index)
{
    // Check if index is valid
    if (index >= m_buffers.size()) {
        return nullptr;
    }

    // Return buffer
    return m_buffers[index];
}

void Mesh::addBuffer(Buffer * buffer)
{
    // Check if buffer is not empty
    if (!buffer) {
        return;
    }

    // Add buffer to geometry
    m_buffers.push_back(buffer);
}

void Mesh::addBuffer(std::unique_ptr<Buffer> && buffer)
{
    // Add buffer
    addBuffer(buffer.get());

    // Transfer ownership of buffer
    m_ownbuffers.push_back(std::move(buffer));
}

Buffer * Mesh::createBuffer(const void * data, unsigned int size)
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

const std::vector< std::unique_ptr<VertexAttribute> > & Mesh::vertexAttributes() const
{
    // Return list of vertex attributes
    return m_vertexAttributes;
}

VertexAttribute * Mesh::addVertexAttribute(Buffer * buffer
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

const std::vector< std::unique_ptr<Geometry> > & Mesh::geometries() const
{
    // Return list of geometries
    return m_geometries;
}

const Geometry * Mesh::geometry(size_t index) const
{
    // Check if index is valid
    if (index >= m_geometries.size()) {
        return nullptr;
    }

    // Return geometry
    return m_geometries[index].get();
}

Geometry * Mesh::geometry(size_t index)
{
    // Check if index is valid
    if (index >= m_geometries.size()) {
        return nullptr;
    }

    // Return geometry
    return m_geometries[index].get();
}

void Mesh::addGeometry(std::unique_ptr<Geometry> && geometry)
{
    // Add geometry
    m_geometries.push_back(std::move(geometry));
}

void Mesh::draw() const
{
    // Draw geometry
    for (auto & geometry : m_geometries) {
        geometry->draw();
    }
}

void Mesh::onDeinit()
{
    // Release GPU-data
    for (auto & geometry : m_geometries) {
        geometry->deinit();
    }
}


} // namespace opengl
} // namespace rendercore
