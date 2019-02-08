
#include <rendercore-gltf/GltfConverter.h>

#include <istream>
#include <iostream>

#include <cppassist/memory/make_unique.h>

#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>

#include <rendercore-opengl/Geometry2.h>

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

void GltfConverter::convert(const Asset & asset)
{
    // Create buffers
    auto buffers = asset.buffers();
    for (auto * buffer : buffers) {
        loadBuffer(buffer->uri());
    }

    // Create meshes
    auto meshes = asset.meshes();
    for (auto * mesh : meshes) {
        createMesh(asset, *mesh);
    }
}

void GltfConverter::loadBuffer(const std::string & path)
{
    // [TODO] Check if path contains BASE64-encoded data
    std::cout << "- " << path << std::endl;

    // Create data buffer
    auto data = cppassist::make_unique< std::vector<char> >();

    // Open file
    auto f = fs::open(path);
    if (f.exists()) {
        // Create input stream
        auto inputStream = f.createInputStream(std::ios::binary);
        if (inputStream && !inputStream->eof()) {
            // Allocate data
            data->resize(f.size());

            // Read data
            inputStream->read(data->data(), f.size());
        }
    }

    // Create buffer
    auto buffer = cppassist::make_unique<rendercore::opengl::Buffer>();
    buffer->setData(*data.get());

    // Save buffer
    m_buffers.push_back(std::move(buffer));
}

void GltfConverter::createMesh(const Asset &, const Mesh &)
{
    /*
    // Process primitives
    for (auto * primitive : mesh.primitives()) {
        // Create primitive
        auto prim = cppassist::make_unique<rendercore::opengl::Geometry2>();
        prim->setMode((gl::GLenum)primitive->mode());
        prim->setMaterial(primitive->material());

        // Set buffers
        for (size_t i=0; i<m_buffers.size(); i++) {
            prim->setBuffer(i, m_buffers[i].get());
        }

        // Set vertex attributes
        size_t index = 0;
        const auto & attributes = primitive->attributes();
        for (auto & it : attributes) {
            // Get attribute
            const std::string & name = it.first;
            size_t attributeIndex = index;

            // Get accessor
            auto * accessor = asset.accessor(it.second);
            if (!accessor) break;

            // Get buffer view
            auto * bufferView = asset.bufferView(accessor->bufferView());
            if (!bufferView) break;

            // Get buffer
            auto * buffer = asset.buffer(bufferView->buffer());
            if (!buffer) break;

            // Get data type
            size_t numComponents = 1;
            auto & dataType = accessor->dataType();
                 if (dataType == "SCALAR") numComponents = 1;
            else if (dataType == "VEC2")   numComponents = 2;
            else if (dataType == "VEC3")   numComponents = 3;
            else if (dataType == "VEC4")   numComponents = 4;

            // Create attribute binding
            prim->setAttributeBinding(
                index,
                attributeIndex,
                bufferView->buffer(),
                bufferView->offset(),
                accessor->offset(),
                bufferView->stride(),
                (gl::GLenum)accessor->componentType(),
                numComponents,
                false
            );

            // Next
            index++;
        }

        // Set index buffer
        int indexBuffer = primitive->indices();
        if (indexBuffer >= 0) {
            // Get accessor
            auto * accessor = asset.accessor(indexBuffer);
            if (accessor) {
                // Get buffer view
                auto * bufferView = asset.bufferView(accessor->bufferView());
                if (bufferView) {
                    // Get buffer
                    auto index = bufferView->buffer();
                    if (index < m_buffers.size()) {
                        // Set index buffer
                        prim->setIndexBuffer(m_buffers[index].get());
                    }
                }
            }
        }
    }
    */
}


} // namespace gltf
} // namespace rendercore
