
#include <rendercore-gltf/GltfConverter.h>

#include <istream>

#include <cppassist/memory/make_unique.h>

#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>

#include <rendercore-opengl/Mesh.h>
#include <rendercore-opengl/Material.h>

#include <rendercore-gltf/Asset.h>
#include <rendercore-gltf/Buffer.h>
#include <rendercore-gltf/Material.h>
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
    // Load data buffers
    auto buffers = asset.buffers();
    for (auto * buffer : buffers) {
        loadData(asset.basePath(), buffer->uri());
    }

    // Generate materials
    auto materials = asset.materials();
    for (auto * material : materials) {
        generateMaterial(asset, *material);
    }

    // Generate meshes
    auto meshes = asset.meshes();
    for (auto * mesh : meshes) {
        generateMesh(asset, *mesh);
    }
}

std::vector< std::unique_ptr<rendercore::opengl::Texture> > & GltfConverter::textures()
{
    return m_textures;
}

std::vector< std::unique_ptr<rendercore::opengl::Material> > & GltfConverter::materials()
{
    return m_materials;
}

std::vector< std::unique_ptr<rendercore::opengl::Mesh> > & GltfConverter::meshes()
{
    return m_meshes;
}

void GltfConverter::generateMaterial(const Asset & asset, const Material & gltfMaterial)
{
    // Create material
    auto material = cppassist::make_unique<rendercore::opengl::Material>();

    // Set attributes
    material->setValue<glm::vec4>("baseColorFactor", gltfMaterial.baseColorFactor());
    material->setValue<float>("metallicFactor", gltfMaterial.metallicFactor());
    material->setValue<float>("roughnessFactor", gltfMaterial.roughnessFactor());
    material->setValue<glm::vec3>("emissiveFactor", gltfMaterial.emissiveFactor());
    material->setValue<std::string>("alphaMode", gltfMaterial.alphaMode());
    material->setValue<float>("alphaCutoff", gltfMaterial.alphaCutoff());
    material->setValue<bool>("doubleSided", gltfMaterial.doubleSided());

    // Set textures
    material->setTexture("baseColorTexture",         loadTexture(asset.basePath(), gltfMaterial.baseColorTexture()));
    material->setTexture("metallicRoughnessTexture", loadTexture(asset.basePath(), gltfMaterial.metallicRoughnessTexture()));
    material->setTexture("normalTexture",            loadTexture(asset.basePath(), gltfMaterial.normalTexture()));
    material->setTexture("occlusionTexture",         loadTexture(asset.basePath(), gltfMaterial.occlusionTexture()));
    material->setTexture("emissiveTexture",          loadTexture(asset.basePath(), gltfMaterial.emissiveTexture()));

    // Save material
    m_materials.push_back(std::move(material));
}

void GltfConverter::generateMesh(const Asset & gltfAsset, const Mesh & gltfMesh)
{
    // Create mesh
    auto mesh = cppassist::make_unique<rendercore::opengl::Mesh>();

    // Caches
    std::unordered_map<size_t, opengl::VertexAttribute *> vertexAttributes;
    std::unordered_map<size_t, opengl::Buffer *>          bufferViews;

    // Process primitives
    for (auto * gltfPrimitive : gltfMesh.primitives()) {
        // Create geometry
        auto geometry = cppassist::make_unique<rendercore::opengl::Geometry>();
        geometry->setMode((gl::GLenum)gltfPrimitive->mode());
        geometry->setMaterial(gltfPrimitive->material() < m_materials.size() ? m_materials[gltfPrimitive->material()].get() : nullptr);

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

            // Get or create buffer view
            opengl::Buffer * buffer = nullptr;
            if (bufferViews.count(bufferViewIndex) > 0) {
                buffer = bufferViews.at(bufferViewIndex);
            } else {
                // Get data
                std::vector<char> * data = (bufferIndex < m_data.size()) ? m_data[bufferIndex].get() : nullptr;
                if (data) {
                    // Create buffer
                    buffer = mesh->createBuffer(data->data() + gltfBufferView->offset(), gltfBufferView->size());

                    // Save buffer for later use
                    bufferViews[bufferViewIndex] = buffer;
                } else break;
            }

            // Get or create vertex attribute
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
                vertexAttribute = mesh->addVertexAttribute(
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
            geometry->bindAttribute(attributeIndex, vertexAttribute);
        }

        // Set index buffer
        int indexBuffer = gltfPrimitive->indices();
        if (indexBuffer >= 0) {
            // Get accessor
            auto * gltfAccessor = gltfAsset.accessor(indexBuffer);
            if (gltfAccessor) {
                // Get buffer view
                auto bufferViewIndex = gltfAccessor->bufferView();
                auto * gltfBufferView = gltfAsset.bufferView(bufferViewIndex);
                if (gltfBufferView) {
                    // Get buffer
                    size_t bufferIndex = gltfBufferView->buffer();
                    auto * gltfBuffer = gltfAsset.buffer(bufferIndex);
                    if (gltfBuffer) {
                        // Get or create buffer
                        opengl::Buffer * buffer = nullptr;
                        if (bufferViews.count(bufferViewIndex) > 0) {
                            buffer = bufferViews.at(bufferViewIndex);
                        } else {
                            // Get data
                            std::vector<char> * data = (bufferIndex < m_data.size()) ? m_data[bufferIndex].get() : nullptr;
                            if (data) {
                                // Create buffer
                                buffer = mesh->createBuffer(data->data() + gltfBufferView->offset(), gltfBufferView->size());
                            }
                        }

                        // Set index buffer
                        if (buffer) {
                            geometry->setIndexBuffer(buffer, (gl::GLenum)gltfAccessor->componentType());
                            geometry->setCount(gltfAccessor->count());
                        }
                    }
                }
            }
        }

        // Add geometry to mesh
        mesh->addGeometry(std::move(geometry));
    }

    // Save mesh
    m_meshes.push_back(std::move(mesh));
}

rendercore::opengl::Texture * GltfConverter::loadTexture(const std::string & basePath, const std::string & filename)
{
    // Check filename
    if (filename == "") {
        return nullptr;
    }

    // Create texture
    auto texture = cppassist::make_unique<rendercore::opengl::Texture>();
    auto * texturePtr = texture.get();

    // Load texture
    texture->load(basePath + filename);

    // Save texture
    m_textures.push_back(std::move(texture));

    // Return texture :)
    return texturePtr;
}

void GltfConverter::loadData(const std::string & basePath, const std::string & filename)
{
    // [TODO] Check if filename contains BASE64-encoded data

    // Create data
    auto data = cppassist::make_unique< std::vector<char> >();

    // Open file
    auto f = fs::open(basePath + filename);
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

    // Save data
    m_data.push_back(std::move(data));
}


} // namespace gltf
} // namespace rendercore
