
#include <rendercore-gltf/GltfLoader.h>

#include <algorithm>
#include <iostream>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/JSON.h>
#include <cppexpose/Object.h>


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

bool GltfLoader::load(const std::string & path)
{
    Object root;

    // Load GLTF file
    if (!JSON::load(root, path)) {
        return false;
    }

    // Parse file
    return parseFile(root);
}

bool GltfLoader::parseFile(const cppexpose::Object & root)
{
    bool res = true;

    // Create asset
    Asset asset;

    // Get object properties
    const auto & properties = root.properties();

    // Check if mandatory data is present
    if (!root.propertyExists("asset")) {
        // Error, 'asset' is mandatory
        return false;
    }

    // Parse properties
    for (auto it : properties) {
        // Get name and value
        std::string key = it.first;
        auto * value    = it.second;

        // Parse element
        if (key == "asset") {
            res &= parseAsset(asset, value);
        } else if (key == "scene") {
            res &= parseDefaultScene(asset, value);
        } else if (key == "scenes") {
            res &= parseScenes(asset, value);
        } else if (key == "nodes") {
            res &= parseNodes(asset, value);
        } else if (key == "meshes") {
            res &= parseMeshes(asset, value);
        } else if (key == "animations") {
            res &= parseAnimations(asset, value);
        } else if (key == "accessors") {
            res &= parseAccessors(asset, value);
        } else if (key == "materials") {
            res &= parseMaterials(asset, value);
        } else if (key == "buffers") {
            res &= parseBuffers(asset, value);
        } else if (key == "bufferViews") {
            res &= parseBufferViews(asset, value);
        }
    }

    // Done
    return res;
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
    // Value must be an unsigned int
    if (!value->canConvert<unsigned int>()) {
        return false;
    }

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
    } else return false;

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
    } else return false;

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

bool GltfLoader::parseMaterials(Asset &, const cppexpose::AbstractVar * value)
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
    } else return false;

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
