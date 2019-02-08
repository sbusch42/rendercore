
#include <rendercore-gltf/Asset.h>


namespace rendercore
{
namespace gltf
{


Asset::Asset()
: m_version(0.0f)
, m_minVersion(0.0f)
, m_scene(-1)
{
}

Asset::~Asset()
{
}

float Asset::version() const
{
    return m_version;
}

void Asset::setVersion(float version)
{
    m_version = version;
}

float Asset::minimumVersion() const
{
    return m_minVersion;
}

void Asset::setMinimumVersion(float version)
{
    m_minVersion = version;
}

int Asset::defaultScene() const
{
    return m_scene;
}

void Asset::setDefaultScene(int scene)
{
    m_scene = scene;
}

std::vector<Scene *> Asset::scenes() const
{
    std::vector<Scene *> lst;

    for (auto & scene : m_scenes) {
        lst.push_back(scene.get());
    }

    return lst;
}

Scene * Asset::scene(size_t index) const
{
    if (index < m_scenes.size()) {
        return m_scenes[index].get();
    } else {
        return nullptr;
    }
}

void Asset::addScene(std::unique_ptr<Scene> && scene)
{
    m_scenes.push_back(std::move(scene));
}

std::vector<Node *> Asset::nodes() const
{
    std::vector<Node *> lst;

    for (auto & node : m_nodes) {
        lst.push_back(node.get());
    }

    return lst;
}

Node * Asset::node(size_t index) const
{
    if (index < m_nodes.size()) {
        return m_nodes[index].get();
    } else {
        return nullptr;
    }
}

void Asset::addNode(std::unique_ptr<Node> && node)
{
    m_nodes.push_back(std::move(node));
}

std::vector<Buffer *> Asset::buffers() const
{
    std::vector<Buffer *> lst;

    for (auto & buffer : m_buffers) {
        lst.push_back(buffer.get());
    }

    return lst;
}

Buffer * Asset::buffer(size_t index) const
{
    if (index < m_buffers.size()) {
        return m_buffers[index].get();
    } else {
        return nullptr;
    }
}

void Asset::addBuffer(std::unique_ptr<Buffer> && buffer)
{
    m_buffers.push_back(std::move(buffer));
}

std::vector<BufferView *> Asset::bufferViews() const
{
    std::vector<BufferView *> lst;

    for (auto & bufferView : m_bufferViews) {
        lst.push_back(bufferView.get());
    }

    return lst;
}

BufferView * Asset::bufferView(size_t index) const
{
    if (index < m_bufferViews.size()) {
        return m_bufferViews[index].get();
    } else {
        return nullptr;
    }
}

void Asset::addBufferView(std::unique_ptr<BufferView> && bufferView)
{
    m_bufferViews.push_back(std::move(bufferView));
}

std::vector<Accessor *> Asset::accessors() const
{
    std::vector<Accessor *> lst;

    for (auto & accessor : m_accessors) {
        lst.push_back(accessor.get());
    }

    return lst;
}

Accessor * Asset::accessor(size_t index) const
{
    if (index < m_accessors.size()) {
        return m_accessors[index].get();
    } else {
        return nullptr;
    }
}

void Asset::addAccessor(std::unique_ptr<Accessor> && accessor)
{
    m_accessors.push_back(std::move(accessor));
}

std::vector<Mesh *> Asset::meshes() const
{
    std::vector<Mesh *> lst;

    for (auto & mesh : m_meshes) {
        lst.push_back(mesh.get());
    }

    return lst;
}

Mesh * Asset::mesh(size_t index) const
{
    if (index < m_meshes.size()) {
        return m_meshes[index].get();
    } else {
        return nullptr;
    }
}

void Asset::addMesh(std::unique_ptr<Mesh> && mesh)
{
    m_meshes.push_back(std::move(mesh));
}


} // namespace gltf
} // namespace rendercore
