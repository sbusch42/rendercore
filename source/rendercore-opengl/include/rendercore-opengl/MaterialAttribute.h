
#pragma once


#include <string>

#include <glm/fwd.hpp>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Material attribute type
*/
enum class AttributeType : unsigned int
{
    Unknown = 0,
    Integer,
    UnsignedInteger,
    Float,
    Boolean,
    String,
    Vec2,
    Vec3,
    Vec4,
    Mat3,
    Mat4
};

/**
*  @brief
*    Helper to get the material attribute type for a data type
*/
template <typename Type>
class AttributeTypeFor
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<int>
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<unsigned int>
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<float>
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<bool>
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<std::string>
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<glm::vec2>
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<glm::vec3>
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<glm::vec4>
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<glm::mat3>
{
public:
    static AttributeType type();
};

template <>
class RENDERCORE_OPENGL_API AttributeTypeFor<glm::mat4>
{
public:
    static AttributeType type();
};

/**
*  @brief
*    Material attribute
*/
class RENDERCORE_OPENGL_API AbstractMaterialAttribute
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] type
    *    Attribute type
    */
    AbstractMaterialAttribute(AttributeType type);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractMaterialAttribute();

    /**
    *  @brief
    *    Get attribute type
    *
    *  @return
    *    Attribute type
    */
    AttributeType type() const;

protected:
    AttributeType m_type; ///< Attribute type
};

/**
*  @brief
*    Typed material attribute
*/
template <typename Type>
class MaterialAttribute : public AbstractMaterialAttribute
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    MaterialAttribute(const Type & value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~MaterialAttribute();

    /**
    *  @brief
    *    Get value
    *
    *  @return
    *    Attribute value
    */
    const Type & value() const;

    /**
    *  @brief
    *    Set value
    *
    *  @param[in] value
    *    Attribute value
    */
    void setValue(const Type & value);

protected:
    Type m_value; ///< Attribute value
};


} // namespace opengl
} // namespace rendercore


#include <rendercore-opengl/MaterialAttribute.inl>
