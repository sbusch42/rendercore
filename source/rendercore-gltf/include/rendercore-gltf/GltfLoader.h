
#pragma once


#include <memory>

#include <rendercore-gltf/rendercore-gltf_api.h>


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
    void load(const std::string & path);
};


} // namespace gltf
} // namespace rendercore
