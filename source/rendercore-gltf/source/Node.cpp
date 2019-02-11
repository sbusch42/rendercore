
#include <rendercore-gltf/Node.h>


namespace rendercore
{
namespace gltf
{


Node::Node()
: m_camera(-1)
, m_mesh(-1)
, m_hasMatrix(false)
, m_translation(0.0f, 0.0f, 0.0f)
, m_rotation(0.0f, 0.0f, 0.0f, 1.0f)
, m_scale(1.0f, 1.0f, 1.0f)
{
}

Node::~Node()
{
}

const std::string & Node::name() const
{
    return m_name;
}

void Node::setName(const std::string & name)
{
    m_name = name;
}

bool Node::hasMatrix() const
{
    return m_hasMatrix;
}

glm::mat4 Node::matrix() const
{
    return m_matrix;
}

void Node::setMatrix(const glm::mat4 & matrix)
{
    m_hasMatrix = true;
    m_matrix    = matrix;
}

glm::vec3 Node::translation() const
{
    return m_translation;
}

void Node::setTranslation(const glm::vec3 & translation)
{
    m_translation = translation;
}

glm::vec4 Node::rotation() const
{
    return m_rotation;
}

void Node::setRotation(const glm::vec4 & rotation)
{
    m_rotation = rotation;
}

glm::vec3 Node::scale() const
{
    return m_scale;
}

void Node::setScale(const glm::vec3 & scale)
{
    m_scale = scale;
}

const std::vector<unsigned int> & Node::children() const
{
    return m_children;
}

void Node::setChildren(const std::vector<unsigned int> & children)
{
    m_children = children;
}

int Node::camera() const
{
    return m_camera;
}

void Node::setCamera(int camera)
{
    m_camera = camera;
}

int Node::mesh() const
{
    return m_mesh;
}

void Node::setMesh(int mesh)
{
    m_mesh = mesh;
}


} // namespace gltf
} // namespace rendercore
