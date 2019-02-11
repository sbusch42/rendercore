
#include <rendercore/scene/SceneNodeComponent.h>


namespace rendercore
{


SceneNodeComponent::SceneNodeComponent()
: m_node(nullptr)
{
}

SceneNodeComponent::~SceneNodeComponent()
{
}

SceneNode * SceneNodeComponent::node() const
{
    return m_node;
}


} // namespace rendercore
