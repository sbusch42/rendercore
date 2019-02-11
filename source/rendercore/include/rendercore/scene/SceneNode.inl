
#pragma once


namespace rendercore
{


template <typename Type>
std::vector<const Type *> SceneNode::components() const
{
    std::vector<const Type *> list;

    // Iterate over components
    for (auto & it : m_components) {
        // Get component
        const auto * component = it.get();

        // Check component type
        const auto * typedComponent = dynamic_cast<const Type *>(component);
        if (typedComponent) {
            // Add to list
            list.push_back(typedComponent);
        }
    }

    // Return list of typed components
    return list;
}

template <typename Type>
std::vector<Type *> SceneNode::components()
{
    std::vector<Type *> list;

    // Iterate over components
    for (auto & it : m_components) {
        // Get component
        auto * component = it.get();

        // Check component type
        auto * typedComponent = dynamic_cast<Type *>(component);
        if (typedComponent) {
            // Add to list
            list.push_back(typedComponent);
        }
    }

    // Return list of typed components
    return list;
}

template <typename Type>
const Type * SceneNode::component() const
{
    // Iterate over components
    for (auto & it : m_components) {
        // Get component
        const auto * component = it.get();

        // Check component type
        const auto * typedComponent = dynamic_cast<const Type *>(component);
        if (typedComponent) {
            // Component found
            return typedComponent;
        }
    }

    // No component of that type found
    return nullptr;
}

template <typename Type>
Type * SceneNode::component()
{
    // Iterate over components
    for (auto & it : m_components) {
        // Get component
        auto * component = it.get();

        // Check component type
        auto * typedComponent = dynamic_cast<Type *>(component);
        if (typedComponent) {
            // Component found
            return typedComponent;
        }
    }

    // No component of that type found
    return nullptr;
}


} // namespace rendercore
