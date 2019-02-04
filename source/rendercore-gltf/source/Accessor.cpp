
#include <rendercore-gltf/Accessor.h>


namespace rendercore
{
namespace gltf
{


Accessor::Accessor()
: m_bufferView(0)
, m_componentType(0)
, m_offset(0)
, m_count(0)
{
}

Accessor::~Accessor()
{
}

unsigned int Accessor::bufferView() const
{
    return m_bufferView;
}

void Accessor::setBufferView(unsigned int bufferView)
{
    m_bufferView = bufferView;
}

const std::string & Accessor::dataType() const
{
    return m_dataType;
}

void Accessor::setDataType(const std::string & dataType)
{
    m_dataType = dataType;
}

unsigned int Accessor::componentType() const
{
    return m_componentType;
}

void Accessor::setComponentType(unsigned int componentType)
{
    m_componentType = componentType;
}

unsigned int Accessor::offset() const
{
    return m_offset;
}

void Accessor::setOffset(unsigned int offset)
{
    m_offset = offset;
}

unsigned int Accessor::count() const
{
    return m_count;
}

void Accessor::setCount(unsigned int count)
{
    m_count = count;
}

std::vector<float> Accessor::minValue() const
{
    return m_minValue;
}

void Accessor::setMinValue(const std::vector<float> & minValue)
{
    m_minValue = minValue;
}

std::vector<float> Accessor::maxValue() const
{
    return m_maxValue;
}

void Accessor::setMaxValue(const std::vector<float> & maxValue)
{
    m_maxValue = maxValue;
}


} // namespace gltf
} // namespace rendercore
