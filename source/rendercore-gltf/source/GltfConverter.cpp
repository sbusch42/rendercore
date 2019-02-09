
#include <rendercore-gltf/GltfConverter.h>

#include <istream>

#include <cppassist/memory/make_unique.h>

#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>

#include <rendercore-opengl/Geometry.h>

#include <rendercore-gltf/Asset.h>
#include <rendercore-gltf/Buffer.h>
#include <rendercore-gltf/Mesh.h>


using namespace cppfs;


using namespace rendercore::opengl;


namespace rendercore
{
namespace gltf
{


GltfConverter::GltfConverter()
{
}

GltfConverter::~GltfConverter()
{
}

void GltfConverter::convert(const Asset & asset, const std::string & basePath)
{
    // Create buffers
    auto buffers = asset.buffers();
    for (auto * buffer : buffers) {
        loadBuffer(basePath, buffer->uri());
    }

    // Create buffer views
    auto bufferViews = asset.bufferViews();
    for (auto * bufferView : bufferViews) {
        loadBufferView(asset, *bufferView);
    }

    // Create meshes
    auto meshes = asset.meshes();
    for (auto * mesh : meshes) {
        createMesh(asset, *mesh);
    }
}

rendercore::opengl::Geometry * GltfConverter::geometry()
{
    rendercore::opengl::Geometry * geometry = nullptr;

    if (m_meshes.size() > 0) {
        geometry = m_meshes[0].get();
    }

    for (size_t i=0; i<m_meshes.size(); i++) {
        m_meshes[i].release();
    }

    for (size_t i=0; i<m_bufferViews.size(); i++) {
        m_bufferViews[i].release();
    }

    return geometry;
}

void GltfConverter::loadBuffer(const std::string & basePath, const std::string & path)
{
    // [TODO] Check if path contains BASE64-encoded data

    // Create data buffer
    auto buffer = cppassist::make_unique< std::vector<char> >();

    // Open file
    auto f = fs::open(basePath + "/" + path);
    if (f.exists()) {
        // Create input stream
        auto inputStream = f.createInputStream(std::ios::binary);
        if (inputStream && !inputStream->eof()) {
            // Allocate data
            buffer->resize(f.size());

            // Read data
            inputStream->read(buffer->data(), f.size());
        }
    }

    // Save buffer
    m_buffers.push_back(std::move(buffer));
}

void GltfConverter::loadBufferView(const Asset &, const BufferView & view)
{
    // Get buffer index
    auto bufferIndex = view.buffer();
    if (bufferIndex < m_buffers.size()) {
        // Get buffer
        std::vector<char> * buffer = m_buffers[bufferIndex].get();

        // Create buffer for buffer view
        auto bufferView = cppassist::make_unique<rendercore::opengl::Buffer>();
        bufferView->setData(buffer->data() + view.offset(), view.size());

        // Save buffer
        m_bufferViews.push_back(std::move(bufferView));
    } else {
        // Invalid buffer
        m_bufferViews.push_back(nullptr);
    }
}

void GltfConverter::createMesh(const Asset & gltfAsset, const Mesh & gltfMesh)
{
    // Create geometry
    auto geometry = cppassist::make_unique<rendercore::opengl::Geometry>();

    // Cache of vertex attribute
    std::unordered_map<size_t, opengl::VertexAttribute *> vertexAttributes;

    // Process primitives
    for (auto * gltfPrimitive : gltfMesh.primitives()) {
        // Create primitive
        auto primitive = cppassist::make_unique<rendercore::opengl::Primitive>();
        primitive->setMode((gl::GLenum)gltfPrimitive->mode());
        primitive->setMaterial(gltfPrimitive->material());

        // Process vertex attributes
        const auto & attributes = gltfPrimitive->attributes();
        for (auto & it : attributes) {
            // Get attribute
            std::string name = it.first;
            size_t attributeIndex = 10;
            if (name == "POSITION") attributeIndex = 0;
            if (name == "connect" || name == "signals") continue;

            // Get GLTF accessor
            size_t accessorIndex = it.second;
            auto * gltfAccessor = gltfAsset.accessor(accessorIndex);
            if (!gltfAccessor) break;

            // Get GLTF buffer view
            size_t bufferViewIndex = gltfAccessor->bufferView();
            auto * gltfBufferView = gltfAsset.bufferView(bufferViewIndex);
            if (!gltfBufferView) break;

            // Get GLTF buffer
            size_t bufferIndex = gltfBufferView->buffer();
            auto * gltfBuffer = gltfAsset.buffer(bufferIndex);
            if (!gltfBuffer) break;

            // Get buffer
            opengl::Buffer * buffer = bufferViewIndex < m_bufferViews.size() ? m_bufferViews[bufferViewIndex].get() : nullptr;

            // Get corresponding vertex attribute
            opengl::VertexAttribute * vertexAttribute = nullptr;
            if (vertexAttributes.count(accessorIndex) > 0) {
                vertexAttribute = vertexAttributes.at(accessorIndex);
            } else {
                // Get data type
                size_t numComponents = 1;
                auto & dataType = gltfAccessor->dataType();
                     if (dataType == "SCALAR") numComponents = 1;
                else if (dataType == "VEC2")   numComponents = 2;
                else if (dataType == "VEC3")   numComponents = 3;
                else if (dataType == "VEC4")   numComponents = 4;
                else if (dataType == "MAT2")   numComponents = 4;
                else if (dataType == "MAT3")   numComponents = 9;
                else if (dataType == "MAT4")   numComponents = 16;

                // Create vertex attribute
                vertexAttribute = geometry->addVertexAttribute(
                    buffer,
                    gltfAccessor->offset(),
                    0,
                    gltfBufferView->stride(),
                    (gl::GLenum)gltfAccessor->componentType(),
                    numComponents,
                    false
                );

                // Save vertex attribute for later use
                vertexAttributes[accessorIndex] = vertexAttribute;
            }

            // Bind vertex attribute
            primitive->bindAttribute(attributeIndex, vertexAttribute);
        }

        // Set index buffer
        int indexBuffer = gltfPrimitive->indices();
        if (indexBuffer >= 0) {
            // Get accessor
            auto * gltfAccessor = gltfAsset.accessor(indexBuffer);
            if (gltfAccessor) {
                // Get buffer view
                auto index = gltfAccessor->bufferView();
                if (index < m_bufferViews.size()) {
                    // Set index buffer
                    primitive->setIndexBuffer(m_bufferViews[index].get(), (gl::GLenum)gltfAccessor->componentType());
                    primitive->setCount(gltfAccessor->count());
                }
            }
        }

        // Add primitive to geometry
        geometry->addPrimitive(std::move(primitive));
    }

    // Save mesh
    m_meshes.push_back(std::move(geometry));
}


} // namespace gltf
} // namespace rendercore
