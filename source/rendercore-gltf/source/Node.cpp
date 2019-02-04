
#include <rendercore-gltf/Node.h>


namespace rendercore
{
namespace gltf
{


Node::Node()
: m_camera(-1)
, m_hasMatrix(false)
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

int Node::camera() const
{
    return m_camera;
}

void Node::setCamera(int camera)
{
    m_camera = camera;
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


} // namespace gltf
} // namespace rendercore
