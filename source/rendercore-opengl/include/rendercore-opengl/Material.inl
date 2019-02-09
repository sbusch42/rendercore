
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
        // Get or create attribute
        auto * attr = m_attributes.at(name).get();
        if (attr && attr->type() == AttributeTypeFor<Type>::type()) {
            // Set value
            static_cast< MaterialAttribute<Type> * >(attr)->setValue(value);
        } else if (!attr) {
            // Create attribute
            auto * typedAttr = new MaterialAttribute<Type>(value);

            // Add attribute
            std::unique_ptr<AbstractMaterialAttribute> ptr(typedAttr);
            m_attributes[name] = std::move(ptr);
        }
    }
}


} // namespace opengl
} // namespace rendercore
