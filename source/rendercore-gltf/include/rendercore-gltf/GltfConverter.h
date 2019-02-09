
#pragma once


#include <memory>
#include <string>
#include <vector>

#include <rendercore-opengl/Geometry.h>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


class Asset;
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
    *    Get meshes
    *
    *  @return
    *    List of loaded meshes
    */
    std::vector< std::unique_ptr<rendercore::opengl::Geometry> > & meshes();

protected:
    void generateMesh(const Asset & asset, const Mesh & mesh);

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
    std::vector< std::unique_ptr< std::vector<char> > >          m_data;   ///< Loaded data buffers
    std::vector< std::unique_ptr<rendercore::opengl::Geometry> > m_meshes; ///< List of meshes
};


} // namespace gltf
} // namespace rendercore
