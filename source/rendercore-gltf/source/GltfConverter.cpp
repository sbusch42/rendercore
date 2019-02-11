
#include <rendercore-gltf/GltfConverter.h>

#include <istream>

#include <cppassist/memory/make_unique.h>

#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>

#include <rendercore-opengl/enums.h>
#include <rendercore-opengl/Mesh.h>
#include <rendercore-opengl/Material.h>
#include <rendercore-opengl/scene/MeshComponent.h>

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

    // Generate scenes
    auto scenes = asset.scenes();
    for (auto * scene : scenes) {
        generateScene(asset, *scene);
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

std::vector< std::unique_ptr<rendercore::Scene> > & GltfConverter::scenes()
{
    return m_scenes;
}

void GltfConverter::generateMaterial(const Asset & asset, const Material & gltfMaterial)
{
    // Create material
    auto material = cppassist::make_unique<rendercore::opengl::Material>();

    // Set attributes
    material->setValue<glm::vec4>  ("baseColorFactor", gltfMaterial.baseColorFactor());
    material->setValue<float>      ("metallicFactor",  gltfMaterial.metallicFactor());
    material->setValue<float>      ("roughnessFactor", gltfMaterial.roughnessFactor());
    material->setValue<glm::vec3>  ("emissiveFactor",  gltfMaterial.emissiveFactor());
    material->setValue<std::string>("alphaMode",       gltfMaterial.alphaMode());
    material->setValue<float>      ("alphaCutoff",     gltfMaterial.alphaCutoff());
    material->setValue<bool>       ("doubleSided",     gltfMaterial.doubleSided());

    // Set textures
    material->setTexture("baseColor",         loadTexture(asset.basePath(), gltfMaterial.baseColorTexture()));
    material->setTexture("metallicRoughness", loadTexture(asset.basePath(), gltfMaterial.metallicRoughnessTexture()));
    material->setTexture("normal",            loadTexture(asset.basePath(), gltfMaterial.normalTexture()));
    material->setTexture("occlusion",         loadTexture(asset.basePath(), gltfMaterial.occlusionTexture()));
    material->setTexture("emissive",          loadTexture(asset.basePath(), gltfMaterial.emissiveTexture()));

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
            if (name == "connect" || name == "signals") {
                continue;
            }

            // Determine attribute index
            unsigned int attributeIndex = 2342; // invalid value
            if (name == "POSITION")   attributeIndex = (unsigned int)AttributeIndex::Position;
            if (name == "NORMAL")     attributeIndex = (unsigned int)AttributeIndex::Normal;
            if (name == "TANGENT")    attributeIndex = (unsigned int)AttributeIndex::Tangent;
            if (name == "TEXCOORD_0") attributeIndex = (unsigned int)AttributeIndex::TexCoord0;
            if (name == "TEXCOORD_1") attributeIndex = (unsigned int)AttributeIndex::TexCoord1;
            if (name == "TEXCOORD_2") attributeIndex = (unsigned int)AttributeIndex::TexCoord2;
            if (name == "TEXCOORD_3") attributeIndex = (unsigned int)AttributeIndex::TexCoord3;
            if (name == "COLOR_0")    attributeIndex = (unsigned int)AttributeIndex::Color0;
            if (name == "COLOR_1")    attributeIndex = (unsigned int)AttributeIndex::Color1;
            if (name == "COLOR_2")    attributeIndex = (unsigned int)AttributeIndex::Color2;
            if (name == "COLOR_3")    attributeIndex = (unsigned int)AttributeIndex::Color3;
            if (attributeIndex == 2342) {
                continue;
            }

            // Get GLTF accessor
            unsigned int accessorIndex = it.second;
            auto * gltfAccessor = gltfAsset.accessor(accessorIndex);
            if (!gltfAccessor) break;

            // Get GLTF buffer view
            unsigned int bufferViewIndex = gltfAccessor->bufferView();
            auto * gltfBufferView = gltfAsset.bufferView(bufferViewIndex);
            if (!gltfBufferView) break;

            // Get GLTF buffer
            unsigned int bufferIndex = gltfBufferView->buffer();
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

void GltfConverter::generateScene(const Asset & gltfAsset, const Scene & gltfScene)
{
    // Create scene
    auto scene = cppassist::make_unique<rendercore::Scene>();

    // Get nodes
    auto gltfNodes = gltfAsset.nodes();

    // Helper function: Get scene node by index
    auto getNode = [&gltfNodes] (unsigned int index) -> const Node * {
        if (index < gltfNodes.size()) {
            return gltfNodes[index];
        }

        return nullptr;
    };

    // Helper function: Parse scene node
    std::function<void (rendercore::SceneNode & parent, const Node * gltfNode)> parseNode;
    parseNode = [&] (rendercore::SceneNode & parent, const Node * gltfNode) {
        // Create scene node
        auto node = cppassist::make_unique<rendercore::SceneNode>();

        // Set transformation
        Transform transform;
        if (gltfNode->hasMatrix()) {
            transform.setTransform(gltfNode->matrix());
        } else {
            transform.setTranslation(gltfNode->translation());
            transform.setRotation(gltfNode->rotation());
            transform.setScale(gltfNode->scale());
        }

        // Set mesh
        int meshIndex = gltfNode->mesh();
        if (meshIndex >= 0 && meshIndex < (int)m_meshes.size()) {
            // Create mesh component
            auto meshComponent = cppassist::make_unique<MeshComponent>();
            meshComponent->setMesh(m_meshes[meshIndex].get());

            // Add component to scene node
            node->addComponent(std::move(meshComponent));
        }

        // Process child nodes
        for (unsigned int index : gltfNode->children()) {
            auto * childNode = getNode(index);
            if (childNode) parseNode(*node.get(), childNode);
        }

        // Add scene node to parent
        parent.addChild(std::move(node));
    };

    // Parse scene starting at the root nodes
    rendercore::SceneNode & root = *scene->root();
    for (unsigned int index : gltfScene.rootNodes()) {
        auto * rootNode = getNode(index);
        if (rootNode) parseNode(root, rootNode);
    }

    // Save scene
    m_scenes.push_back(std::move(scene));
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
