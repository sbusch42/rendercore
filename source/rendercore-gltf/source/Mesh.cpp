
#include <rendercore-gltf/Mesh.h>


namespace rendercore
{
namespace gltf
{


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

std::vector<Primitive *> Mesh::primitives() const
{
    std::vector<Primitive *> lst;

    for (auto & primitive : m_primitives) {
        lst.push_back(primitive.get());
    }

    return lst;
}

void Mesh::addPrimitive(std::unique_ptr<Primitive> && primitive)
{
    m_primitives.push_back(std::move(primitive));
}


} // namespace gltf
} // namespace rendercore
