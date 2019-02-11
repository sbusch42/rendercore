
#pragma once


#include <rendercore/scene/SceneNode.h>


namespace rendercore
{


/**
*  @brief
*    Represents a virtual 3D scene
*/
class RENDERCORE_API Scene
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
    virtual ~Scene();

    /**
    *  @brief
    *    Get root node
    *
    *  @return
    *    Scene node (never null)
    */
    const SceneNode * root() const;

    /**
    *  @brief
    *    Get root node
    *
    *  @return
    *    Scene node (never null)
    */
    SceneNode * root();

    /**
    *  @brief
    *    Set root node
    *
    *  @param[in] node
    *    Scene node (must NOT be null)
    */
    void setRoot(std::unique_ptr<SceneNode> && node);

protected:
    std::unique_ptr<SceneNode> m_root; ///< Root node of the scene
};


} // namespace rendercore
