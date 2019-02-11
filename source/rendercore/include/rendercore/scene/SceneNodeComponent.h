
#pragma once


#include <rendercore/rendercore_api.h>


namespace rendercore
{


class SceneNode;


/**
*  @brief
*    Represents a component of a scene node
*/
class RENDERCORE_API SceneNodeComponent
{
    friend class SceneNode;

public:
    /**
    *  @brief
    *    Constructor
    */
    SceneNodeComponent();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~SceneNodeComponent();

    /**
    *  @brief
    *    Get node to which the component belongs
    *
    *  @return
    *    Scene node (can be null)
    */
    SceneNode * node() const;

protected:
    SceneNode * m_node; ///< Scene node to which the component belongs (can be null)
};


} // namespace rendercore
