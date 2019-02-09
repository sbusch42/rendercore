
#include <rendercore/Transform.h>

#include <glm/gtx/transform.hpp>


using namespace glm;


namespace rendercore
{


Transform::Transform()
: m_rotation(0.0f, 0.0f, 0.0f, 1.0f)
, m_translation(0.0f, 0.0f, 0.0f)
, m_scale(1.0f)
{
}

Transform::~Transform()
{
}

const glm::quat & Transform::rotation() const
{
    // Return rotation
    return m_rotation;
}

void Transform::setRotation(const glm::quat & rotation)
{
    // Set rotation
    m_rotation = rotation;

    // Reset transformation matrix
    m_transform.invalidate();
}

const glm::vec3 & Transform::translation() const
{
    // Return translation
    return m_translation;
}

void Transform::setTranslation(const glm::vec3 & translation)
{
    // Set translation
    m_translation = translation;

    // Reset transformation matrix
    m_transform.invalidate();
}

const glm::vec3 & Transform::scale() const
{
    // Return scale
    return m_scale;
}

void Transform::setScale(const glm::vec3 & scale)
{
    // Set scale
    m_scale = scale;

    // Reset transformation matrix
    m_transform.invalidate();
}

const glm::mat4 & Transform::transform() const
{
    // Check if transformation matrix needs to be recalculated
    if (!m_transform.isValid()) {
        // Calculate transformation matrix
        glm::mat4 transform = glm::mat4(1.0);
        transform = glm::translate(transform, m_translation);
        transform = glm::scale(transform, m_scale);
        transform = transform * glm::toMat4(m_rotation);

        // Update transformation matrix
        m_transform.setValue(transform);
    }

    // Return transformation matrix
    return m_transform.value();
}


} // namespace rendercore
