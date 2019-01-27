
#pragma once


namespace rendercore
{
namespace opengl
{


template <typename VectorType>
void Geometry::setData(size_t index, const std::vector<VectorType> & data, gl::GLenum usage)
{
    buffer(index)->setData(data, usage);
}

template <typename ArrayType, size_t ArraySize>
void Geometry::setData(size_t index, const std::array<ArrayType, ArraySize> & data, gl::GLenum usage)
{
    buffer(index)->setData(data, usage);
}


} // namespace opengl
} // namespace rendercore
