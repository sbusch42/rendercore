
#include <rendercore-opengl/scene/MeshComponent.h>


namespace rendercore
{
namespace opengl
{


MeshComponent::MeshComponent()
: m_mesh(nullptr)
{
}

MeshComponent::~MeshComponent()
{
}

const Mesh * MeshComponent::mesh() const
{
    return m_mesh;
}

Mesh * MeshComponent::mesh()
{
    return m_mesh;
}

void MeshComponent::setMesh(Mesh * mesh)
{
    m_mesh = mesh;
}


} // namespace opengl
} // namespace rendercore
