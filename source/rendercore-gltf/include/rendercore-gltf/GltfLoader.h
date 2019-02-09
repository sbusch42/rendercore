
#pragma once


#include <string>
#include <vector>
#include <map>

#include <glm/glm.hpp>

#include <rendercore-gltf/Asset.h>
#include <rendercore-gltf/Mesh.h>


namespace cppexpose {
    class AbstractVar;
    class Object;
}


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    GLTF 2.0 loader
*/
class RENDERCORE_GLTF_API GltfLoader
{
public:
    /**
    *  @brief
    *    Constructor
    */
    GltfLoader();

    /**
    *  @brief
    *    Destructor
    */
    ~GltfLoader();

    /**
    *  @brief
    *    Load GLTF file
    *
    *  @param[in] path
    *    Path to file
    *
    *  @return
    *    Loaded asset (can be null)
    */
    std::unique_ptr<Asset> load(const std::string & path);

protected:
    // GLTF parsing
    std::unique_ptr<Asset> parseFile(const cppexpose::Object & root, const std::string & basePath);
    bool parseAsset(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseDefaultScene(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseScenes(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseScene(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseNodes(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseNode(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseMeshes(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseMesh(Asset & asset, const cppexpose::AbstractVar * value);
    bool parsePrimitives(Mesh & mesh, const cppexpose::AbstractVar * value);
    bool parsePrimitive(Mesh & mesh, const cppexpose::AbstractVar * value);
    bool parseAnimations(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseAccessors(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseAccessor(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseMaterials(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseMaterial(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseBuffers(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseBuffer(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseBufferViews(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseBufferView(Asset & asset, const cppexpose::AbstractVar * value);

    // General parsing functions
    std::map<std::string, unsigned int> parseIntMap(const cppexpose::AbstractVar * value);
    std::vector<unsigned int> parseIntArray(const cppexpose::AbstractVar * value);
    std::vector<float> parseFloatArray(const cppexpose::AbstractVar * value);
    glm::vec2 parseVec2(const cppexpose::AbstractVar * value);
    glm::vec3 parseVec3(const cppexpose::AbstractVar * value);
    glm::vec4 parseVec4(const cppexpose::AbstractVar * value);
    glm::mat4 parseMat4(const cppexpose::AbstractVar * value);
};


} // namespace gltf
} // namespace rendercore
