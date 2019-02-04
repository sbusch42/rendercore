
#pragma once


#include <string>
#include <vector>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Scene
*/
class RENDERCORE_GLTF_API Scene
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Scene();

    /**
    *  @brief
    *    Destructor
    */
    ~Scene();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Scene name
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Set name
    *
    *  @param[in] name
    *    Scene name
    */
    void setName(const std::string & name);

    /**
    *  @brief
    *    Get root nodes
    *
    *  @return
    *    Indices of root nodes
    */
    const std::vector<unsigned int> & rootNodes() const;

    /**
    *  @brief
    *    Set root nodes
    *
    *  @param[in] nodes
    *    Indices of root nodes
    */
    void setRootNodes(const std::vector<unsigned int> & nodes);

protected:
    std::string               m_name;  ///< Scene name
    std::vector<unsigned int> m_nodes; ///< Indices of root nodes
};


} // namespace gltf
} // namespace rendercore
