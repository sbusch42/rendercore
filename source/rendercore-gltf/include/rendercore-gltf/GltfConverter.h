
#pragma once


#include <memory>
#include <string>
#include <vector>

#include <rendercore-opengl/Buffer.h>
#include <rendercore-opengl/Geometry.h>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


class Asset;
class BufferView;
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
    void convert(const Asset & asset, const std::string & basePath);

    rendercore::opengl::Geometry * geometry();

protected:
    /**
    *  @brief
    *    Load binary buffer data from external file
    *
    *  @param[in] path
    *    Path to file
    */
    void loadBuffer(const std::string & basePath, const std::string & path);

    // [TODO]
    void loadBufferView(const Asset & asset, const BufferView & bufferView);
    void createMesh(const Asset & asset, const Mesh & mesh);

protected:
    std::vector< std::unique_ptr< std::vector<char> > >          m_buffers;     ///< List of buffers
    std::vector< std::unique_ptr<rendercore::opengl::Buffer> >   m_bufferViews; ///< List of buffer views
    std::vector< std::unique_ptr<rendercore::opengl::Geometry> > m_meshes;      ///< List of meshes
};


} // namespace gltf
} // namespace rendercore
