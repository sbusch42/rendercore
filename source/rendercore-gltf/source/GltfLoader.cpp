
#include <rendercore-gltf/GltfLoader.h>

#include <algorithm>

#include <cppassist/memory/make_unique.h>

#include <cppfs/FilePath.h>

#include <cppexpose/JSON.h>
#include <cppexpose/Object.h>


using namespace cppfs;
using namespace cppexpose;


namespace rendercore
{
namespace gltf
{


GltfLoader::GltfLoader()
{
}

GltfLoader::~GltfLoader()
{
}

std::unique_ptr<Asset> GltfLoader::load(const std::string & path)
{
    Object root;

    // Load GLTF file
    if (!JSON::load(root, path)) {
        return false;
    }

    // Get base directory
    std::string basePath = FilePath(path).directoryPath();

    // Parse file
    return parseFile(root, basePath);
}

std::unique_ptr<Asset> GltfLoader::parseFile(const cppexpose::Object & root, const std::string & basePath)
{
    bool res = true;

    // Create asset
    std::unique_ptr<Asset> asset = cppassist::make_unique<Asset>();
    asset->setBasePath(basePath);

    // Get object properties
    const auto & properties = root.properties();

    // Check if mandatory data is present
    if (!root.propertyExists("asset")) {
        // Error, 'asset' is mandatory
        return nullptr;
    }

    // Parse properties
    for (auto it : properties) {
        // Get name and value
        std::string key = it.first;
        auto * value    = it.second;

        // Parse element
        if (key == "asset") {
            res &= parseAsset(*asset.get(), value);
        } else if (key == "scene") {
            res &= parseDefaultScene(*asset.get(), value);
        } else if (key == "scenes") {
            res &= parseScenes(*asset.get(), value);
        } else if (key == "nodes") {
            res &= parseNodes(*asset.get(), value);
        } else if (key == "meshes") {
            res &= parseMeshes(*asset.get(), value);
        } else if (key == "animations") {
            // [TODO]
            // res &= parseAnimations(*asset.get(), value);
        } else if (key == "accessors") {
            res &= parseAccessors(*asset.get(), value);
        } else if (key == "materials") {
            res &= parseMaterials(*asset.get(), value);
        } else if (key == "buffers") {
            res &= parseBuffers(*asset.get(), value);
        } else if (key == "bufferViews") {
            res &= parseBufferViews(*asset.get(), value);
        } else if (key == "textures") {
            res &= parseTextures(*asset.get(), value);
        } else if (key == "samplers") {
            res &= parseSamplers(*asset.get(), value);
        } else if (key == "images") {
            res &= parseImages(*asset.get(), value);
        }
    }

    // [TODO] Check for errors
    return std::move(asset);
}

bool GltfLoader::parseAsset(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'version' (mandatory)
    if (obj.propertyExists("version")) {
        asset.setVersion(obj.property("version")->convert<float>());
    } else return false;

    // 'minVersion'
    if (obj.propertyExists("minVersion")) {
        asset.setMinimumVersion(obj.property("minVersion")->convert<float>());
    }

    // Done
    return true;
}

bool GltfLoader::parseDefaultScene(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Get default scene
    asset.setDefaultScene(value->convert<int>());

    // Done
    return true;
}

bool GltfLoader::parseScenes(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse scenes
    for (size_t i=0; i<array.size(); i++) {
        res &= parseScene(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseScene(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create scene
    auto scene = cppassist::make_unique<Scene>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'name'
    if (obj.propertyExists("name")) {
        scene->setName(obj.property("name")->convert<std::string>());
    }

    // 'nodes'
    if (obj.propertyExists("nodes")) {
        // Get node indices
        scene->setRootNodes(parseIntArray(obj.property("nodes")));
    }

    // Add scene
    asset.addScene(std::move(scene));

    // Done
    return true;
}

bool GltfLoader::parseNodes(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse nodes
    for (size_t i=0; i<array.size(); i++) {
        res &= parseNode(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseNode(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create node
    auto node = cppassist::make_unique<Node>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'name'
    if (obj.propertyExists("name")) {
        node->setName(obj.property("name")->convert<std::string>());
    }

    // 'matrix'
    if (obj.propertyExists("matrix")) {
        node->setMatrix(parseMat4(obj.property("matrix")));
    }

    // 'translation'
    if (obj.propertyExists("translation")) {
        node->setTranslation(parseVec3(obj.property("translation")));
    }

    // 'rotation'
    if (obj.propertyExists("rotation")) {
        node->setRotation(parseVec4(obj.property("rotation")));
    }

    // 'scale'
    if (obj.propertyExists("scale")) {
        node->setScale(parseVec3(obj.property("scale")));
    }

    // 'children'
    if (obj.propertyExists("children")) {
        node->setChildren(parseIntArray(obj.property("children")));
    }

    // 'mesh'
    if (obj.propertyExists("mesh")) {
        // Get attached mesh index
        node->setMesh(obj.property("mesh")->convert<int>());
    }

    // 'camera'
    if (obj.propertyExists("camera")) {
        // Get attached camera index
        node->setCamera(obj.property("camera")->convert<int>());
    }

    // Add node
    asset.addNode(std::move(node));

    // Done
    return true;
}

bool GltfLoader::parseMeshes(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse meshes
    for (size_t i=0; i<array.size(); i++) {
        res &= parseMesh(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseMesh(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create mesh
    auto mesh = cppassist::make_unique<Mesh>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'primitives' (mandatory)
    if (obj.propertyExists("primitives")) {
        parsePrimitives(*mesh.get(), obj.property("primitives"));
    } else return false;

    // Add mesh
    asset.addMesh(std::move(mesh));

    // Done
    return true;
}

bool GltfLoader::parsePrimitives(Mesh & mesh, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse primitives
    for (size_t i=0; i<array.size(); i++) {
        res &= parsePrimitive(mesh, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parsePrimitive(Mesh & mesh, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create primitive
    auto primitive = cppassist::make_unique<Primitive>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'mode'
    if (obj.propertyExists("mode")) {
        primitive->setMode(obj.property("mode")->convert<unsigned int>());
    };

    // 'material'
    if (obj.propertyExists("material")) {
        primitive->setMaterial(obj.property("material")->convert<unsigned int>());
    }

    // 'indices'
    if (obj.propertyExists("indices")) {
        primitive->setIndices(obj.property("indices")->convert<int>());
    }

    // 'attributes'
    if (obj.propertyExists("attributes")) {
        primitive->setAttributes(parseIntMap(obj.property("attributes")));
    } else return false;

    // 'targets'
    if (obj.propertyExists("targets")) {
        // [TODO]
        return false;
    }

    // Add primitive
    mesh.addPrimitive(std::move(primitive));

    // Done
    return true;
}

bool GltfLoader::parseAnimations(Asset &, const cppexpose::AbstractVar * value)
{
    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    // const cppexpose::Array & array = *value->asArray();

    // [TODO]
    return false;
}

bool GltfLoader::parseAccessors(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse accessors
    for (size_t i=0; i<array.size(); i++) {
        res &= parseAccessor(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseAccessor(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create accessor
    auto accessor = cppassist::make_unique<Accessor>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'bufferView'
    if (obj.propertyExists("bufferView")) {
        accessor->setBufferView(obj.property("bufferView")->convert<unsigned int>());
    } else return false;

    // 'byteOffset'
    if (obj.propertyExists("byteOffset")) {
        accessor->setOffset(obj.property("byteOffset")->convert<unsigned int>());
    };

    // 'count'
    if (obj.propertyExists("count")) {
        accessor->setCount(obj.property("count")->convert<unsigned int>());
    } else return false;

    // 'componentType'
    if (obj.propertyExists("componentType")) {
        accessor->setComponentType(obj.property("componentType")->convert<unsigned int>());
    }

    // 'type'
    if (obj.propertyExists("type")) {
        accessor->setDataType(obj.property("type")->convert<std::string>());
    }

    // 'min'
    if (obj.propertyExists("min")) {
        accessor->setMinValue(parseFloatArray(obj.property("min")));
    }

    // 'max'
    if (obj.propertyExists("max")) {
        accessor->setMaxValue(parseFloatArray(obj.property("max")));
    }

    // 'sparse'
    if (obj.propertyExists("sparse")) {
        // [TODO]
        return false;
    }

    // Add buffer view
    asset.addAccessor(std::move(accessor));

    // Done
    return true;
}

bool GltfLoader::parseMaterials(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse materials
    for (size_t i=0; i<array.size(); i++) {
        res &= parseMaterial(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseMaterial(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create material
    auto material = cppassist::make_unique<Material>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'name'
    if (obj.propertyExists("name")) {
        material->setName(obj.property("name")->convert<std::string>());
    }

    // 'pbrMetallicRoughness'
    if (obj.propertyExists("pbrMetallicRoughness")) {
        // Get object
        const cppexpose::Object * subObj = obj.property("pbrMetallicRoughness")->asObject();
        if (subObj) {
            // 'baseColorFactor'
            if (subObj->propertyExists("baseColorFactor")) {
                material->setBaseColorFactor(parseVec4(subObj->property("baseColorFactor")));
            }

            // 'baseColorTexture'
            if (subObj->propertyExists("baseColorTexture")) {
                // Get object
                const cppexpose::Object * subObj2 = subObj->property("baseColorTexture")->asObject();
                if (subObj2) {
                    // Create texture info
                    auto textureInfo = cppassist::make_unique<TextureInfo>();

                    // 'index'
                    if (subObj2->propertyExists("index")) {
                        textureInfo->setTexture(subObj2->property("index")->convert<unsigned int>());
                    }

                    // 'texCoord'
                    if (subObj2->propertyExists("texCoord")) {
                        textureInfo->setUVSet(subObj2->property("texCoord")->convert<unsigned int>());
                    }

                    // Add texture info
                    asset.addTextureInfo(std::move(textureInfo));

                    // Set base color texture info
                    material->setBaseColorTexture(asset.textureInfos().size() - 1);
                }
            }

            // 'metallicFactor'
            if (subObj->propertyExists("metallicFactor")) {
                material->setMetallicFactor(subObj->property("metallicFactor")->convert<float>());
            }

            // 'roughnessFactor'
            if (subObj->propertyExists("roughnessFactor")) {
                material->setRoughnessFactor(subObj->property("roughnessFactor")->convert<float>());
            }

            // 'metallicRoughnessTexture'
            if (subObj->propertyExists("metallicRoughnessTexture")) {
                // Get object
                const cppexpose::Object * subObj2 = subObj->property("metallicRoughnessTexture")->asObject();
                if (subObj2) {
                    // Create texture info
                    auto textureInfo = cppassist::make_unique<TextureInfo>();

                    // 'index'
                    if (subObj2->propertyExists("index")) {
                        textureInfo->setTexture(subObj2->property("index")->convert<unsigned int>());
                    }

                    // 'texCoord'
                    if (subObj2->propertyExists("texCoord")) {
                        textureInfo->setUVSet(subObj2->property("texCoord")->convert<unsigned int>());
                    }

                    // Add texture info
                    asset.addTextureInfo(std::move(textureInfo));

                    // Set base color texture info
                    material->setMetallicRoughnessTexture(asset.textureInfos().size() - 1);
                }
            }
        }
    }

    // 'normalTexture'
    if (obj.propertyExists("normalTexture")) {
        // Get object
        const cppexpose::Object * subObj = obj.property("normalTexture")->asObject();
        if (subObj) {
            // Create texture info
            auto textureInfo = cppassist::make_unique<TextureInfo>();

            // 'index'
            if (subObj->propertyExists("index")) {
                textureInfo->setTexture(subObj->property("index")->convert<unsigned int>());
            }

            // 'texCoord'
            if (subObj->propertyExists("texCoord")) {
                textureInfo->setUVSet(subObj->property("texCoord")->convert<unsigned int>());
            }

            // 'scale'
            if (subObj->propertyExists("scale")) {
                textureInfo->setScale(subObj->property("scale")->convert<float>());
            }

            // Add texture info
            asset.addTextureInfo(std::move(textureInfo));

            // Set normal texture info
            material->setNormalTexture(asset.textureInfos().size() - 1);
        }
    }

    // 'occlusionTexture'
    if (obj.propertyExists("occlusionTexture")) {
        // Get object
        const cppexpose::Object * subObj = obj.property("occlusionTexture")->asObject();
        if (subObj) {
            // Create texture info
            auto textureInfo = cppassist::make_unique<TextureInfo>();

            // 'index'
            if (subObj->propertyExists("index")) {
                textureInfo->setTexture(subObj->property("index")->convert<unsigned int>());
            }

            // 'texCoord'
            if (subObj->propertyExists("texCoord")) {
                textureInfo->setUVSet(subObj->property("texCoord")->convert<unsigned int>());
            }

            // 'strength'
            if (subObj->propertyExists("strength")) {
                textureInfo->setStrength(subObj->property("strength")->convert<float>());
            }

            // Add texture info
            asset.addTextureInfo(std::move(textureInfo));

            // Set normal texture info
            material->setOcclusionTexture(asset.textureInfos().size() - 1);
        }
    }

    // 'emissiveTexture'
    if (obj.propertyExists("emissiveTexture")) {
        // Get object
        const cppexpose::Object * subObj = obj.property("emissiveTexture")->asObject();
        if (subObj) {
            // Create texture info
            auto textureInfo = cppassist::make_unique<TextureInfo>();

            // 'index'
            if (subObj->propertyExists("index")) {
                textureInfo->setTexture(subObj->property("index")->convert<unsigned int>());
            }

            // 'texCoord'
            if (subObj->propertyExists("texCoord")) {
                textureInfo->setUVSet(subObj->property("texCoord")->convert<unsigned int>());
            }

            // Add texture info
            asset.addTextureInfo(std::move(textureInfo));

            // Set emissive texture info
            material->setEmissiveTexture(asset.textureInfos().size() - 1);
        }
    }

    // 'emissiveFactor'
    if (obj.propertyExists("emissiveFactor")) {
        material->setEmissiveFactor(parseVec3(obj.property("emissiveFactor")));
    }

    // 'alphaMode'
    if (obj.propertyExists("alphaMode")) {
        material->setAlphaMode(obj.property("alphaMode")->convert<std::string>());
    }

    // 'alphaCutoff'
    if (obj.propertyExists("alphaCutoff")) {
        material->setAlphaCutoff(obj.property("alphaCutoff")->convert<float>());
    }

    // 'doubleSided'
    if (obj.propertyExists("doubleSided")) {
        material->setDoubleSided(obj.property("doubleSided")->convert<bool>());
    }

    // Add material
    asset.addMaterial(std::move(material));

    // Done
    return true;
}

bool GltfLoader::parseBuffers(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse buffers
    for (size_t i=0; i<array.size(); i++) {
        res &= parseBuffer(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseBuffer(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create buffer
    auto buffer = cppassist::make_unique<Buffer>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'byteLength'
    if (obj.propertyExists("byteLength")) {
        buffer->setSize(obj.property("byteLength")->convert<unsigned int>());
    } else return false;

    // 'uri'
    if (obj.propertyExists("uri")) {
        buffer->setUri(obj.property("uri")->convert<std::string>());
    } else return false;

    // Add buffer
    asset.addBuffer(std::move(buffer));

    // Done
    return true;
}

bool GltfLoader::parseBufferViews(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse buffer views
    for (size_t i=0; i<array.size(); i++) {
        res &= parseBufferView(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseBufferView(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create buffer view
    auto bufferView = cppassist::make_unique<BufferView>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'buffer'
    if (obj.propertyExists("buffer")) {
        bufferView->setBuffer(obj.property("buffer")->convert<unsigned int>());
    } else return false;

    // 'byteOffset'
    if (obj.propertyExists("byteOffset")) {
        bufferView->setOffset(obj.property("byteOffset")->convert<unsigned int>());
    };

    // 'byteLength'
    if (obj.propertyExists("byteLength")) {
        bufferView->setSize(obj.property("byteLength")->convert<unsigned int>());
    } else return false;

    // 'byteStride'
    if (obj.propertyExists("byteStride")) {
        bufferView->setStride(obj.property("byteStride")->convert<unsigned int>());
    }

    // 'target'
    if (obj.propertyExists("target")) {
        bufferView->setTarget(obj.property("target")->convert<unsigned int>());
    }

    // Add buffer view
    asset.addBufferView(std::move(bufferView));

    // Done
    return true;
}

bool GltfLoader::parseTextures(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse textures
    for (size_t i=0; i<array.size(); i++) {
        res &= parseTexture(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseTexture(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create texture
    auto texture = cppassist::make_unique<Texture>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'name'
    if (obj.propertyExists("name")) {
        texture->setName(obj.property("name")->convert<std::string>());
    }

    // 'sampler'
    if (obj.propertyExists("sampler")) {
        texture->setSampler(obj.property("sampler")->convert<int>());
    }

    // 'source'
    if (obj.propertyExists("source")) {
        texture->setImage(obj.property("source")->convert<int>());
    }

    // Add texture
    asset.addTexture(std::move(texture));

    // Done
    return true;
}

bool GltfLoader::parseSamplers(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse samplers
    for (size_t i=0; i<array.size(); i++) {
        res &= parseSampler(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseSampler(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create sampler
    auto sampler = cppassist::make_unique<Sampler>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'name'
    if (obj.propertyExists("name")) {
        sampler->setName(obj.property("name")->convert<std::string>());
    }

    // 'minFilter'
    if (obj.propertyExists("minFilter")) {
        sampler->setMinFilter(obj.property("minFilter")->convert<unsigned int>());
    }

    // 'magFilter'
    if (obj.propertyExists("magFilter")) {
        sampler->setMinFilter(obj.property("magFilter")->convert<unsigned int>());
    }

    // 'wrapS'
    if (obj.propertyExists("wrapS")) {
        sampler->setWrapS(obj.property("wrapS")->convert<unsigned int>());
    }

    // 'wrapT'
    if (obj.propertyExists("wrapT")) {
        sampler->setWrapS(obj.property("wrapT")->convert<unsigned int>());
    }

    // Add sampler
    asset.addSampler(std::move(sampler));

    // Done
    return true;
}

bool GltfLoader::parseImages(Asset & asset, const cppexpose::AbstractVar * value)
{
    bool res = true;

    // Value must be an array
    if (!value->isArray()) {
        return false;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse images
    for (size_t i=0; i<array.size(); i++) {
        res &= parseImage(asset, array.at(i));
    }

    // Done
    return res;
}

bool GltfLoader::parseImage(Asset & asset, const cppexpose::AbstractVar * value)
{
    // Value must be an object
    if (!value->isObject()) {
        return false;
    }

    // Create image
    auto image = cppassist::make_unique<Image>();

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // 'name'
    if (obj.propertyExists("name")) {
        image->setName(obj.property("name")->convert<std::string>());
    }

    // 'uri'
    if (obj.propertyExists("uri")) {
        image->setURI(obj.property("uri")->convert<std::string>());
    }

    // 'mimeType'
    if (obj.propertyExists("mimeType")) {
        image->setMimeType(obj.property("mimeType")->convert<std::string>());
    }

    // 'bufferView'
    if (obj.propertyExists("bufferView")) {
        image->setBufferView(obj.property("bufferView")->convert<unsigned int>());
    }

    // Add image
    asset.addImage(std::move(image));

    // Done
    return true;
}

std::map<std::string, unsigned int> GltfLoader::parseIntMap(const cppexpose::AbstractVar * value)
{
    std::map<std::string, unsigned int> map;

    // Value must be an object
    if (!value->isObject()) {
        return map;
    }

    // Get object
    const cppexpose::Object & obj = *value->asObject();

    // Get object properties
    const auto & properties = obj.properties();

    // Parse map
    for (auto it : properties) {
        // Get name and value
        std::string key = it.first;
        auto * value    = it.second;

        // Add value to map
        map.insert({ key, value->convert<unsigned int>() });
    }

    // Return value
    return map;
}

std::vector<unsigned int> GltfLoader::parseIntArray(const cppexpose::AbstractVar * value)
{
    std::vector<unsigned int> vec;

    // Value must be an array
    if (!value->isArray()) {
        return vec;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse vector
    for (size_t i=0; i<array.size(); i++) {
        vec.push_back(array.at(i)->convert<unsigned int>());
    }

    // Return value
    return vec;
}

std::vector<float> GltfLoader::parseFloatArray(const cppexpose::AbstractVar * value)
{
    std::vector<float> vec;

    // Value must be an array
    if (!value->isArray()) {
        return vec;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse vector
    for (size_t i=0; i<array.size(); i++) {
        vec.push_back(array.at(i)->convert<float>());
    }

    // Return value
    return vec;
}

glm::vec2 GltfLoader::parseVec2(const cppexpose::AbstractVar * value)
{
    glm::vec2 vec(0.0f);

    // Value must be an array
    if (!value->isArray()) {
        return vec;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse vector
    for (size_t i=0; i<std::min(array.size(), (size_t)2); i++) {
        vec[i] = array.at(i)->convert<float>();
    }

    // Return value
    return vec;
}

glm::vec3 GltfLoader::parseVec3(const cppexpose::AbstractVar * value)
{
    glm::vec3 vec(0.0f);

    // Value must be an array
    if (!value->isArray()) {
        return vec;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse vector
    for (size_t i=0; i<std::min(array.size(), (size_t)3); i++) {
        vec[i] = array.at(i)->convert<float>();
    }

    // Return value
    return vec;
}

glm::vec4 GltfLoader::parseVec4(const cppexpose::AbstractVar * value)
{
    glm::vec4 vec(0.0f);

    // Value must be an array
    if (!value->isArray()) {
        return vec;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse vector
    for (size_t i=0; i<std::min(array.size(), (size_t)4); i++) {
        vec[i] = array.at(i)->convert<float>();
    }

    // Return value
    return vec;
}

glm::mat4 GltfLoader::parseMat4(const cppexpose::AbstractVar * value)
{
    glm::mat4 mat(0.0f);

    // Value must be an array
    if (!value->isArray()) {
        return mat;
    }

    // Get array
    const cppexpose::Array & array = *value->asArray();

    // Parse matrix
    for (size_t i=0; i<std::min(array.size(), (size_t)16); i++) {
        mat[i/4][i%4] = array.at(i)->convert<float>();
    }

    // Return value
    return mat;
}


} // namespace gltf
} // namespace rendercore
