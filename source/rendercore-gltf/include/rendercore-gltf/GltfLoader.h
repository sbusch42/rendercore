
#pragma once


#include <string>
#include <vector>
#include <map>

#include <glm/glm.hpp>

#include <rendercore-gltf/rendercore-gltf_api.h>


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
    */
    bool load(const std::string & path);

protected:
    struct Scene {
        std::string name;
        std::vector<unsigned int> nodes;
    };

    struct Node {
        std::string name;
        int attachedCamera;
        bool hasMatrix;
        glm::mat4 matrix;
        glm::vec3 translation;
        glm::vec4 rotation;
        glm::vec3 scale;
        std::vector<unsigned int> children;
    };

    struct Buffer {
        unsigned int byteLength;
        std::string uri;
    };

    struct BufferView {
        unsigned int buffer;
        unsigned int byteOffset;
        unsigned int byteLength;
        unsigned int byteStride;
        unsigned int target;
    };

    struct Accessor {
        unsigned int       bufferView;
        unsigned int       byteOffset;
        unsigned int       count;
        unsigned int       componentType;
        std::string        type;
        std::vector<float> min;
        std::vector<float> max;
    };

    struct Primitive {
        unsigned int mode;
        unsigned int material;
        unsigned int indices;
        std::map<std::string, unsigned int> attributes;
    };

    struct Mesh {
        std::vector<Primitive> primitives;
    };

    struct Asset {
        float                   version;
        float                   minVersion;
        int                     initialScene;
        std::vector<Scene>      scenes;
        std::vector<Node>       nodes;
        std::vector<Buffer>     buffers;
        std::vector<BufferView> bufferViews;
        std::vector<Accessor>   accessors;
        std::vector<Mesh>       meshes;
    };

protected:
    bool parseFile(const cppexpose::Object & root);
    bool parseAsset(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseInitialScene(Asset & asset, const cppexpose::AbstractVar * value);
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
    bool parseBuffers(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseBuffer(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseBufferViews(Asset & asset, const cppexpose::AbstractVar * value);
    bool parseBufferView(Asset & asset, const cppexpose::AbstractVar * value);

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
