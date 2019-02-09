
#pragma once


#include <memory>
#include <string>
#include <vector>

#include <rendercore-opengl/Geometry.h>
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
    std::vector< std::unique_ptr<rendercore::opengl::Geometry> > & meshes();

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
    *    Load texture from external file
    *
    *  @param[in] basePath
    *    Path to directory
    *  @param[in] filename
    *    Filename
    */
    rendercore::opengl::Texture * loadTexture(const std::string & basePath, const std::string & filename);

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
    std::vector< std::unique_ptr<rendercore::opengl::Geometry> > m_meshes;    ///< List of meshes
};


} // namespace gltf
} // namespace rendercore
