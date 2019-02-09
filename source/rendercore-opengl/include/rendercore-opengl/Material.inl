
#pragma once


namespace rendercore
{
namespace opengl
{


template <typename Type>
Type Material::value(const std::string & name) const
{
    // Check if attribute exists
    if (m_attributes.count(name) > 0) {
        // Get attribute
        const auto * attr = m_attributes.at(name).get();
        if (attr && attr->type() == AttributeTypeFor<Type>::type()) {
            // Return value
            return static_cast< const MaterialAttribute<Type> * >(attr)->value();
        }
    }

    // Return default value
    return Type();
}

template <typename Type>
void Material::setValue(const std::string & name, const Type & value)
{
    // Check if attribute exists
    if (m_attributes.count(name) > 0) {
        // Get attribute
        auto * attr = m_attributes.at(name).get();
        if (attr->type() == AttributeTypeFor<Type>::type()) {
            // Set value
            static_cast< MaterialAttribute<Type> * >(attr)->setValue(value);
        }
    } else {
        // Create attribute
        std::unique_ptr<AbstractMaterialAttribute> typedAttr(new MaterialAttribute<Type>(value));
        m_attributes[name] = std::move(typedAttr);
    }
}


} // namespace opengl
} // namespace rendercore
