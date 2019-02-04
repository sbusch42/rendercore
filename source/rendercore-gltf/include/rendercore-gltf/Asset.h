
#pragma once


#include <memory>
#include <vector>

#include <rendercore-gltf/Scene.h>
#include <rendercore-gltf/Node.h>
#include <rendercore-gltf/Buffer.h>
#include <rendercore-gltf/BufferView.h>
#include <rendercore-gltf/Accessor.h>
#include <rendercore-gltf/Mesh.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    GLTF asset
*/
class RENDERCORE_GLTF_API Asset
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Asset();

    /**
    *  @brief
    *    Destructor
    */
    ~Asset();

    /**
    *  @brief
    *    Get version
    *
    *  @return
    *    GLTF version
    */
    float version() const;

    /**
    *  @brief
    *    Set version
    *
    *  @param[in] version
    *    GLTF version
    */
    void setVersion(float version);

    /**
    *  @brief
    *    Get minimum version to display this asset
    *
    *  @return
    *    GLTF minimum version
    */
    float minimumVersion() const;

    /**
    *  @brief
    *    Set minimum version to display this asset
    *
    *  @param[in] version
    *    GLTF minimum version
    */
    void setMinimumVersion(float version);

    /**
    *  @brief
    *    Get default scene
    *
    *  @return
    *    Scene index
    */
    int defaultScene() const;

    /**
    *  @brief
    *    Set default scene
    *
    *  @param[in] scene
    *    Scene index
    */
    void setDefaultScene(int scene);

    /**
    *  @brief
    *    Get scenes
    *
    *  @return
    *    List of scenes
    */
    std::vector<Scene *> scenes() const;

    /**
    *  @brief
    *    Add scene
    *
    *  @param[in] scene
    *    Scene (must NOT be nullptr)
    */
    void addScene(std::unique_ptr<Scene> && scene);

    /**
    *  @brief
    *    Get nodes
    *
    *  @return
    *    List of nodes
    */
    std::vector<Node *> nodes() const;

    /**
    *  @brief
    *    Add node
    *
    *  @param[in] node
    *    Node (must NOT be nullptr)
    */
    void addNode(std::unique_ptr<Node> && node);

    /**
    *  @brief
    *    Get buffers
    *
    *  @return
    *    List of buffers
    */
    std::vector<Buffer *> buffers() const;

    /**
    *  @brief
    *    Add buffer
    *
    *  @param[in] buffer
    *    Buffer (must NOT be nullptr)
    */
    void addBuffer(std::unique_ptr<Buffer> && buffer);

    /**
    *  @brief
    *    Get buffer views
    *
    *  @return
    *    List of buffer views
    */
    std::vector<BufferView *> bufferViews() const;

    /**
    *  @brief
    *    Add buffer view
    *
    *  @param[in] bufferView
    *    Buffer view (must NOT be nullptr)
    */
    void addBufferView(std::unique_ptr<BufferView> && bufferView);

    /**
    *  @brief
    *    Get accessors
    *
    *  @return
    *    List of accessors
    */
    std::vector<Accessor *> accessors() const;

    /**
    *  @brief
    *    Add accessor
    *
    *  @param[in] accessor
    *    Accessor (must NOT be nullptr)
    */
    void addAccessor(std::unique_ptr<Accessor> && accessor);

    /**
    *  @brief
    *    Get meshes
    *
    *  @return
    *    List of meshes
    */
    std::vector<Mesh *> meshes() const;

    /**
    *  @brief
    *    Add mesh
    *
    *  @param[in] mesh
    *    Mesh (must NOT be nullptr)
    */
    void addMesh(std::unique_ptr<Mesh> && mesh);

protected:
    // Options
    float m_version;    ///< GLTF version
    float m_minVersion; ///< Minimum GLTF version for this asset
    int   m_scene;      ///< Index of default scene (-1 for none)

    // Data
    std::vector< std::unique_ptr<Scene> >      m_scenes;
    std::vector< std::unique_ptr<Node> >       m_nodes;
    std::vector< std::unique_ptr<Buffer> >     m_buffers;
    std::vector< std::unique_ptr<BufferView> > m_bufferViews;
    std::vector< std::unique_ptr<Accessor> >   m_accessors;
    std::vector< std::unique_ptr<Mesh> >       m_meshes;
};


} // namespace gltf
} // namespace rendercore
