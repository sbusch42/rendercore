
#include <rendercore-opengl/Geometry2.h>


namespace rendercore
{
namespace opengl
{


Geometry2::Geometry2(GpuContainer * container)
: GpuObject(container)
{
}

Geometry2::~Geometry2()
{
}

const std::unordered_map< size_t, std::unique_ptr<Buffer> > & Geometry2::buffers() const
{
    return m_buffers;
}

const Buffer * Geometry2::buffer(size_t index) const
{
    if (m_buffers.count(index) == 0) {
        return nullptr;
    }

    return m_buffers.at(index).get();
}

Buffer * Geometry2::buffer(size_t index)
{
    if (m_buffers.count(index) == 0) {
        return nullptr;
    }

    return m_buffers.at(index).get();
}

void Geometry2::setBuffer(size_t index, std::unique_ptr<Buffer> && buffer)
{
    m_buffers[index] = std::move(buffer);
}

const std::vector< std::unique_ptr<Primitive> > & Geometry2::primitives() const
{
    return m_primitives;
}

const Primitive * Geometry2::primitive(size_t index) const
{
    if (index < m_primitives.size()) {
        return m_primitives[index].get();
    }

    return nullptr;
}

void Geometry2::add(std::unique_ptr<Primitive> && primitive)
{
    m_primitives.push_back(std::move(primitive));
}

void Geometry2::onInit()
{
}

void Geometry2::onDeinit()
{
}


} // namespace opengl
} // namespace rendercore
