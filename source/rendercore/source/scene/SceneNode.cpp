
#include <rendercore/scene/SceneNode.h>


namespace rendercore
{


SceneNode::SceneNode()
: m_parent(nullptr)
{
}

SceneNode::~SceneNode()
{
}

SceneNode * SceneNode::parent() const
{
    return m_parent;
}

const std::vector< std::unique_ptr<SceneNode> > & SceneNode::children() const
{
    return m_children;
}

void SceneNode::addChild(std::unique_ptr<SceneNode> && node)
{
    // Check if node is valid
    if (!node.get()) {
        return;
    }

    // Set parent
    node->m_parent = this;

    // Add to list
    m_children.push_back(std::move(node));
}

const std::vector< std::unique_ptr<SceneNodeComponent> > & SceneNode::components() const
{
    return m_components;
}

void SceneNode::addComponent(std::unique_ptr<SceneNodeComponent> && component)
{
    // Check if component is valid
    if (!component.get()) {
        return;
    }

    // Set node
    component->m_node = this;

    // Add to list
    m_components.push_back(std::move(component));
}

const Transform & SceneNode::transform() const
{
    // Return transformation
    return m_transform;
}

void SceneNode::setTransform(const Transform & transform)
{
    // Set transformation
    m_transform = transform;
}


} // namespace rendercore
