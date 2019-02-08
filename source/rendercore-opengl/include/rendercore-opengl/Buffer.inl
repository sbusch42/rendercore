
#pragma once


namespace rendercore
{
namespace opengl
{


template <typename Type>
void Buffer::setData(const std::vector<Type> & data)
{
    this->setData(static_cast<const void *>(data.data()), sizeof(Type) * data.size());
}

template <typename Type, std::size_t Count>
void Buffer::setData(const std::array<Type, Count> & data)
{
    this->setData(static_cast<const void *>(data.data()), sizeof(Type) * Count);
}

template <typename Type>
void Buffer::allocate(unsigned int numElements)
{
    // Calculate size and allocate memory
    allocate(sizeof(Type) * numElements);
}


} // namespace opengl
} // namespace rendercore
