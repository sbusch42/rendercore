
#pragma once


#include <memory>
#include <vector>

#include <rendercore/Transform.h>
#include <rendercore/scene/SceneNodeComponent.h>


namespace rendercore
{


/**
*  @brief
*    Represents a node in a virtual 3D scene
*/
class RENDERCORE_API SceneNode
{
public:
    /**
    *  @brief
    *    Constructor
    */
    SceneNode();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~SceneNode();

    /**
    *  @brief
    *    Get parent node
    *
    *  @return
    *    Parent node (can be null)
    */
    SceneNode * parent() const;

    /**
    *  @brief
    *    Get child nodes
    *
    *  @return
    *    List of child nodes
    */
    const std::vector< std::unique_ptr<SceneNode> > & children() const;

    /**
    *  @brief
    *    Add child node
    *
    *  @param[in] node
    *    Scene node (must NOT be null)
    */
    void addChild(std::unique_ptr<SceneNode> && node);

    /**
    *  @brief
    *    Get components
    *
    *  @return
    *    List of components
    */
    const std::vector< std::unique_ptr<SceneNodeComponent> > & components() const;

    /**
    *  @brief
    *    Get components of a specific kind
    *
    *  @tparam
    *    Component Type (must be derived from SceneNodeComponent)
    *
    *  @return
    *    List of components of that kind
    */
    template <typename Type>
    std::vector<const Type *> components() const;

    /**
    *  @brief
    *    Get components of a specific kind
    *
    *  @tparam
    *    Component Type (must be derived from SceneNodeComponent)
    *
    *  @return
    *    List of components of that kind
    */
    template <typename Type>
    std::vector<Type *> components();

    /**
    *  @brief
    *    Get first component of a specific kind
    *
    *  @tparam
    *    Component Type (must be derived from SceneNodeComponent)
    *
    *  @return
    *    First component of that kind (can be null)
    */
    template <typename Type>
    const Type * component() const;

    /**
    *  @brief
    *    Get first component of a specific kind
    *
    *  @tparam
    *    Component Type (must be derived from SceneNodeComponent)
    *
    *  @return
    *    First component of that kind (can be null)
    */
    template <typename Type>
    Type * component();

    /**
    *  @brief
    *    Add component
    *
    *  @param[in] component
    *    Scene node component (must NOT be null)
    */
    void addComponent(std::unique_ptr<SceneNodeComponent> && component);

    /**
    *  @brief
    *    Get transformation
    *
    *  @return
    *    Transformation of node in 3D space
    */
    const Transform & transform() const;

    /**
    *  @brief
    *    Set transformation
    *
    *  @param[in] transform
    *    Transformation of node in 3D space
    */
    void setTransform(const Transform & transform);

protected:
    SceneNode                                          * m_parent;     ///< Parent node (can be null)
    std::vector< std::unique_ptr<SceneNode> >            m_children;   ///< List of child nodes
    std::vector< std::unique_ptr<SceneNodeComponent> >   m_components; ///< List of components
    Transform                                            m_transform;  ///< Transformation of node in 3D space
};


} // namespace rendercore


#include <rendercore/scene/SceneNode.inl>
