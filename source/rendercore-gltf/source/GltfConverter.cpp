
#include <rendercore-gltf/GltfConverter.h>

#include <istream>

#include <cppassist/memory/make_unique.h>

#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>

#include <rendercore-gltf/Asset.h>
#include <rendercore-gltf/Buffer.h>


using namespace cppfs;


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
    // Load data buffers
    auto buffers = asset.buffers();
    for (auto * buffer : buffers) {
        loadBuffer(buffer->uri());
    }
}

void GltfConverter::loadBuffer(const std::string & path)
{
    // [TODO] Check if path contains BASE64-encoded data

    // Create buffer
    auto buffer = cppassist::make_unique< std::vector<char> >();

    // Open file
    auto f = fs::open(path);
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


} // namespace gltf
} // namespace rendercore
