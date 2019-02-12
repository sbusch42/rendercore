
#pragma once


#include <memory>
#include <string>
#include <vector>

#include <rendercore/scene/Scene.h>

#include <rendercore-opengl/Mesh.h>
#include <rendercore-opengl/Material.h>
#include <rendercore-opengl/Texture.h>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


class Asset;
class Material;
class Mesh;
class Scene;


/**
*  @brief
*    Converter from GTLF data into rendercore objects
*/
class RENDERCORE_GLTF_API GltfConverter
{
public:
    /**
    *  @brief
    *    Constructor
    */
    GltfConverter();

    /**
    *  @brief
    *    Destructor
    */
    ~GltfConverter();

    /**
    *  @brief
    *    Convert GLTF asset
    *
    *  @param[in] asset
    *    GLTF asset
    */
    void convert(const Asset & asset);

    /**
    *  @brief
    *    Get textures
    *
    *  @return
    *    List of loaded textures
    */
    std::vector< std::unique_ptr<rendercore::opengl::Texture> > & textures();

    /**
    *  @brief
    *    Get materials
    *
    *  @return
    *    List of loaded materials
    */
    std::vector< std::unique_ptr<rendercore::opengl::Material> > & materials();

    /**
    *  @brief
    *    Get meshes
    *
    *  @return
    *    List of loaded meshes
    */
    std::vector< std::unique_ptr<rendercore::opengl::Mesh> > & meshes();

    /**
    *  @brief
    *    Get scenes
    *
    *  @return
    *    List of loaded scenes
    */
    std::vector< std::unique_ptr<rendercore::Scene> > & scenes();

protected:
    /**
    *  @brief
    *    Generate material from GLTF data
    *
    *  @param[in] asset
    *    GLTF asset
    *  @param[in] material
    *    GLTF material
    */
    void generateMaterial(const Asset & asset, const Material & material);

    /**
    *  @brief
    *    Generate mesh from GLTF data
    *
    *  @param[in] asset
    *    GLTF asset
    *  @param[in] mesh
    *    GLTF mesh
    */
    void generateMesh(const Asset & asset, const Mesh & mesh);

    /**
    *  @brief
    *    Generate scene from GLTF data
    *
    *  @param[in] asset
    *    GLTF asset
    *  @param[in] scene
    *    GLTF scene
    */
    void generateScene(const Asset & asset, const Scene & scene);

    /**
    *  @brief
    *    Load texture from external file
    *
    *  @param[in] basePath
    *    Path to directory
    *  @param[in] asset
    *    GLTF asset
    *  @param[in] textureInfoIndex
    *    Texture info index
    */
    rendercore::opengl::Texture * loadTexture(const std::string & basePath, const Asset & asset, int textureInfoIndex);

    /**
    *  @brief
    *    Load binary data from external file
    *
    *  @param[in] basePath
    *    Path to directory
    *  @param[in] filename
    *    Filename
    */
    void loadData(const std::string & basePath, const std::string & filename);

protected:
    std::vector< std::unique_ptr< std::vector<char> > >          m_data;      ///< Loaded data buffers
    std::vector< std::unique_ptr<rendercore::opengl::Texture> >  m_textures;  ///< List of textures
    std::vector< std::unique_ptr<rendercore::opengl::Material> > m_materials; ///< List of materials
    std::vector< std::unique_ptr<rendercore::opengl::Mesh> >     m_meshes;    ///< List of meshes
    std::vector< std::unique_ptr<rendercore::Scene> >            m_scenes;    ///< List of scenes
};


} // namespace gltf
} // namespace rendercore
