
#include <cppassist/memory/make_unique.h>

#include <rendercore/scene/Scene.h>


namespace rendercore
{


Scene::Scene()
{
    // Create a root node
    m_root = cppassist::make_unique<SceneNode>();
}

Scene::~Scene()
{
}

const SceneNode * Scene::root() const
{
    return m_root.get();
}

SceneNode * Scene::root()
{
    return m_root.get();
}

void Scene::setRoot(std::unique_ptr<SceneNode> && node)
{
    // Check if node is valid
    if (!node.get()) {
        return;
    }

    // Save root node
    m_root = std::move(node);
}


} // namespace rendercore
