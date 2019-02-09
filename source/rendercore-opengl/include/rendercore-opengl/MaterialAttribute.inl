
#pragma once


namespace rendercore
{
namespace opengl
{



template <typename Type>
AttributeType AttributeTypeFor<Type>::type()
{
    return AttributeType::Unknown;
}

template <typename Type>
MaterialAttribute<Type>::MaterialAttribute(const Type & value)
: AbstractMaterialAttribute(AttributeTypeFor<Type>::type())
, m_value(value)
{
}

template <typename Type>
MaterialAttribute<Type>::~MaterialAttribute()
{
}

template <typename Type>
const Type & MaterialAttribute<Type>::value() const
{
    return m_value;
}

template <typename Type>
void MaterialAttribute<Type>::setValue(const Type & value)
{
    m_value = value;
}


} // namespace opengl
} // namespace rendercore
