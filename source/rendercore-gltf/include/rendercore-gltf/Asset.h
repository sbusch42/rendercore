
#pragma once


#include <memory>
#include <vector>
#include <string>

#include <rendercore-gltf/Scene.h>
#include <rendercore-gltf/Node.h>
#include <rendercore-gltf/Buffer.h>
#include <rendercore-gltf/BufferView.h>
#include <rendercore-gltf/Accessor.h>
#include <rendercore-gltf/Mesh.h>
#include <rendercore-gltf/Material.h>
#include <rendercore-gltf/TextureInfo.h>
#include <rendercore-gltf/Texture.h>
#include <rendercore-gltf/Sampler.h>
#include <rendercore-gltf/Image.h>


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
    *    Get base path
    *
    *  @return
    *    Path to directory from which the asset has been loaded
    */
    const std::string & basePath() const;

    /**
    *  @brief
    *    Set base path
    *
    *  @param[in] path
    *    Path to directory from which the asset has been loaded
    */
    void setBasePath(const std::string & path);

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
    *    Get scene
    *
    *  @param[in] index
    *    Scene index
    *
    *  @return
    *    Scene (can be null)
    */
    Scene * scene(size_t index) const;

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
    *    Get node
    *
    *  @param[in] index
    *    Node index
    *
    *  @return
    *    Node (can be null)
    */
    Node * node(size_t index) const;

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
    *    Get buffer
    *
    *  @param[in] index
    *    Buffer index
    *
    *  @return
    *    Buffer (can be null)
    */
    Buffer * buffer(size_t index) const;

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
    *    Get buffer view
    *
    *  @param[in] index
    *    Buffer view index
    *
    *  @return
    *    Buffer view (can be null)
    */
    BufferView * bufferView(size_t index) const;

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
    *    Get accessor
    *
    *  @param[in] index
    *    Accessor index
    *
    *  @return
    *    Accessor (can be null)
    */
    Accessor * accessor(size_t index) const;

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
    *    Get mesh
    *
    *  @param[in] index
    *    Mesh index
    *
    *  @return
    *    Mesh (can be null)
    */
    Mesh * mesh(size_t index) const;

    /**
    *  @brief
    *    Add mesh
    *
    *  @param[in] mesh
    *    Mesh (must NOT be nullptr)
    */
    void addMesh(std::unique_ptr<Mesh> && mesh);

    /**
    *  @brief
    *    Get materials
    *
    *  @return
    *    List of materials
    */
    std::vector<Material *> materials() const;

    /**
    *  @brief
    *    Get material
    *
    *  @param[in] index
    *    Material index
    *
    *  @return
    *    Material (can be null)
    */
    Material * material(size_t index) const;

    /**
    *  @brief
    *    Add material
    *
    *  @param[in] material
    *    Material (must NOT be nullptr)
    */
    void addMaterial(std::unique_ptr<Material> && material);

    /**
    *  @brief
    *    Get texture infos
    *
    *  @return
    *    List of texture infos
    */
    std::vector<TextureInfo *> textureInfos() const;

    /**
    *  @brief
    *    Get texture info
    *
    *  @param[in] index
    *    Texture info index
    *
    *  @return
    *    Texture info (can be null)
    */
    TextureInfo * textureInfo(size_t index) const;

    /**
    *  @brief
    *    Add texture info
    *
    *  @param[in] textureInfo
    *    Texture info (must NOT be nullptr)
    */
    void addTextureInfo(std::unique_ptr<TextureInfo> && textureInfo);

    /**
    *  @brief
    *    Get textures
    *
    *  @return
    *    List of textures
    */
    std::vector<Texture *> textures() const;

    /**
    *  @brief
    *    Get texture
    *
    *  @param[in] index
    *    Texture index
    *
    *  @return
    *    Texture (can be null)
    */
    Texture * texture(size_t index) const;

    /**
    *  @brief
    *    Add texture
    *
    *  @param[in] texture
    *    Texture (must NOT be nullptr)
    */
    void addTexture(std::unique_ptr<Texture> && texture);

    /**
    *  @brief
    *    Get samplers
    *
    *  @return
    *    List of samplers
    */
    std::vector<Sampler *> samplers() const;

    /**
    *  @brief
    *    Get sampler
    *
    *  @param[in] index
    *    Sampler index
    *
    *  @return
    *    Sampler (can be null)
    */
    Sampler * sampler(size_t index) const;

    /**
    *  @brief
    *    Add sampler
    *
    *  @param[in] sampler
    *    Sampler (must NOT be nullptr)
    */
    void addSampler(std::unique_ptr<Sampler> && sampler);

    /**
    *  @brief
    *    Get images
    *
    *  @return
    *    List of images
    */
    std::vector<Image *> images() const;

    /**
    *  @brief
    *    Get image
    *
    *  @param[in] index
    *    Image index
    *
    *  @return
    *    Image (can be null)
    */
    Image * image(size_t index) const;

    /**
    *  @brief
    *    Add image
    *
    *  @param[in] image
    *    Image (must NOT be nullptr)
    */
    void addImage(std::unique_ptr<Image> && image);

protected:
    // Meta data
    std::string m_basePath;   ///< Path to directory from which the asset has been loaded
    float       m_version;    ///< GLTF version
    float       m_minVersion; ///< Minimum GLTF version for this asset
    int         m_scene;      ///< Index of default scene (-1 for none)

    // Data
    std::vector< std::unique_ptr<Scene> >       m_scenes;
    std::vector< std::unique_ptr<Node> >        m_nodes;
    std::vector< std::unique_ptr<Buffer> >      m_buffers;
    std::vector< std::unique_ptr<BufferView> >  m_bufferViews;
    std::vector< std::unique_ptr<Accessor> >    m_accessors;
    std::vector< std::unique_ptr<Mesh> >        m_meshes;
    std::vector< std::unique_ptr<Material> >    m_materials;
    std::vector< std::unique_ptr<TextureInfo> > m_textureInfos;
    std::vector< std::unique_ptr<Texture> >     m_textures;
    std::vector< std::unique_ptr<Sampler> >     m_samplers;
    std::vector< std::unique_ptr<Image> >       m_images;
};


} // namespace gltf
} // namespace rendercore
