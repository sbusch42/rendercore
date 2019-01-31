
#include <rendercore/Transform.h>

#include <glm/gtx/transform.hpp>


using namespace glm;


namespace rendercore
{


Transform::Transform()
: m_rotationAxis(0.0f, 1.0f, 0.0f)
, m_rotationAngle(0.0f)
, m_translation(0.0f, 0.0f, 0.0f)
, m_scale(1.0f)
{
}

Transform::~Transform()
{
}

const glm::vec3 & Transform::rotationAxis() const
{
    // Return rotation axis
    return m_rotationAxis;
}

void Transform::setRotationAxis(const glm::vec3 & axis)
{
    // Set rotation axis
    m_rotationAxis = axis;

    // Reset transformation matrix
    m_transform.invalidate();
}

float Transform::rotationAngle() const
{
    // Return rotation angle
    return m_rotationAngle;
}

void Transform::setRotationAngle(float angle)
{
    // Set rotation angle
    m_rotationAngle = angle;

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
        transform = glm::rotate(transform, m_rotationAngle, m_rotationAxis);

        // Update transformation matrix
        m_transform.setValue(transform);
    }

    // Return transformation matrix
    return m_transform.value();
}


} // namespace rendercore
