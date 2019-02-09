
#include <rendercore-opengl/Material.h>

#include <algorithm>


namespace rendercore
{
namespace opengl
{


Material::Material(GpuContainer * container)
: GpuObject(container)
{
}

Material::~Material()
{
}

std::vector<std::string> Material::attributes() const
{
    // Get attribute names
    std::vector<std::string> names;
    for (auto & it : m_attributes) {
        names.push_back(it.first);
    }

    // Return list of attribute names
    return names;
}

bool Material::hasAttribute(const std::string & name) const
{
    // Check if attribute exists
    return (m_attributes.count(name) > 0);
}

const AbstractMaterialAttribute * Material::attribute(const std::string & name) const
{
    // Check if attribute exists
    if (m_attributes.count(name) > 0) {
        // Get attribute
        const auto & attr = m_attributes.at(name);
        return attr.get();
    }

    // Attribute does not exist
    return nullptr;
}

void Material::onInit()
{
}

void Material::onDeinit()
{
}


} // namespace opengl
} // namespace rendercore
