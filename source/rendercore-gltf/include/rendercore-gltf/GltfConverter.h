
#pragma once


#include <memory>
#include <string>
#include <vector>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


class Asset;


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

protected:
    /**
    *  @brief
    *    Load binary buffer data from external file
    *
    *  @param[in] path
    *    Path to file
    */
    void loadBuffer(const std::string & path);

protected:
    std::vector< std::unique_ptr<std::vector<char>> > m_buffers; ///< List of data buffers
};


} // namespace gltf
} // namespace rendercore
