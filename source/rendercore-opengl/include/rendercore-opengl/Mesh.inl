
#pragma once


namespace rendercore
{
namespace opengl
{


template <typename Type>
Buffer * Mesh::createBuffer(const std::vector<Type> & data)
{
    return this->createBuffer(static_cast<const void *>(data.data()), sizeof(Type) * data.size());
}

template <typename Type, std::size_t Count>
Buffer * Mesh::createBuffer(const std::array<Type, Count> & data)
{
    return this->createBuffer(static_cast<const void *>(data.data()), sizeof(Type) * Count);
}


} // namespace opengl
} // namespace rendercore
