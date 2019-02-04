
#include <rendercore-gltf/Scene.h>


namespace rendercore
{
namespace gltf
{


Scene::Scene()
{
}

Scene::~Scene()
{
}

const std::string & Scene::name() const
{
    return m_name;
}

void Scene::setName(const std::string & name)
{
    m_name = name;
}

const std::vector<unsigned int> & Scene::rootNodes() const
{
    return m_nodes;
}

void Scene::setRootNodes(const std::vector<unsigned int> & nodes)
{
    m_nodes = nodes;
}


} // namespace gltf
} // namespace rendercore
