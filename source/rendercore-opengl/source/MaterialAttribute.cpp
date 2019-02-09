
#include <rendercore-opengl/MaterialAttribute.h>


namespace rendercore
{
namespace opengl
{


AttributeType AttributeTypeFor<int>::type()
{
    return AttributeType::Integer;
}

AttributeType AttributeTypeFor<unsigned int>::type()
{
    return AttributeType::UnsignedInteger;
}

AttributeType AttributeTypeFor<float>::type()
{
    return AttributeType::Float;
}

AttributeType AttributeTypeFor<bool>::type()
{
    return AttributeType::Boolean;
}

AttributeType AttributeTypeFor<std::string>::type()
{
    return AttributeType::String;
}

AttributeType AttributeTypeFor<glm::vec2>::type()
{
    return AttributeType::Vec2;
}

AttributeType AttributeTypeFor<glm::vec3>::type()
{
    return AttributeType::Vec3;
}

AttributeType AttributeTypeFor<glm::vec4>::type()
{
    return AttributeType::Vec4;
}

AttributeType AttributeTypeFor<glm::mat3>::type()
{
    return AttributeType::Mat3;
}

AttributeType AttributeTypeFor<glm::mat4>::type()
{
    return AttributeType::Mat4;
}

AbstractMaterialAttribute::AbstractMaterialAttribute(AttributeType type)
: m_type(type)
{
}

AbstractMaterialAttribute::~AbstractMaterialAttribute()
{
}

AttributeType AbstractMaterialAttribute::type() const
{
    return m_type;
}


} // namespace opengl
} // namespace rendercore
