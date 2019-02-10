
#include <rendercore/Camera.h>

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>


using namespace glm;


namespace rendercore
{


Camera::Camera()
: m_viewMatrix(1.0f)
, m_projectionMatrix(1.0f)
{
}

Camera::~Camera()
{
}

const mat4 & Camera::viewMatrix() const
{
    return m_viewMatrix;
}

void Camera::setViewMatrix(const glm::mat4 & matrix)
{
    m_viewMatrix = matrix;

    update();
}

const mat4 & Camera::projectionMatrix() const
{
    return m_projectionMatrix;
}

void Camera::setProjectionMatrix(const glm::mat4 & matrix)
{
    m_projectionMatrix = matrix;

    update();
}

const mat4 & Camera::viewProjectionMatrix() const
{
    if (!m_viewProjectionMatrix.isValid()) {
        m_viewProjectionMatrix.setValue(projectionMatrix() * viewMatrix());
    }

    return m_viewProjectionMatrix.value();
}

const mat4 & Camera::viewInvertedMatrix() const
{
    if (!m_viewInvertedMatrix.isValid()) {
        m_viewInvertedMatrix.setValue(inverse(viewMatrix()));
    }

    return m_viewInvertedMatrix.value();
}

const mat4 & Camera::projectionInvertedMatrix() const
{
    if (!m_projectionInvertedMatrix.isValid()) {
        m_projectionInvertedMatrix.setValue(inverse(projectionMatrix()));
    }

    return m_projectionInvertedMatrix.value();
}

const mat4 & Camera::viewProjectionInvertedMatrix() const
{
    if (!m_viewProjectionInvertedMatrix.isValid()) {
        m_viewProjectionInvertedMatrix.setValue(inverse(viewProjectionMatrix()));
    }

    return m_viewProjectionInvertedMatrix.value();
}

const mat3 & Camera::normalMatrix() const
{
    if (!m_normalMatrix.isValid()) {
        m_normalMatrix.setValue(inverseTranspose(mat3(viewMatrix())));
    }

    return m_normalMatrix.value();
}

void Camera::lookAt(const glm::vec3 & eye, const glm::vec3 & center, const glm::vec3 & up)
{
    setViewMatrix(glm::lookAt(eye, center, up));
}

void Camera::perspective(float fovY, float aspect, float zNear, float zFar)
{
    setProjectionMatrix(glm::perspective(fovY, aspect, zNear, zFar));
}

void Camera::perspective(float fovY, const ivec2 &viewport, float zNear, float zFar)
{
    setProjectionMatrix(glm::perspective(fovY, glm::max(float(viewport.x) / viewport.y, 1.0f), zNear, zFar));
}

void Camera::ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
    setProjectionMatrix(glm::ortho(left, right, bottom, top, zNear, zFar));
}

void Camera::ortho(float fovY, float aspect, float zNear, float zFar)
{
    setProjectionMatrix(glm::ortho(-fovY * aspect, fovY * aspect, -fovY, fovY, zNear, zFar));
}

void Camera::orthographicFromPerspective(float fovY, float aspect, float zNear, float zFar, float syncDist)
{
    // Compute ortho params from fovY and aspect, assuming symmetry
    const auto right = zNear*glm::tan(fovY/2.f);
    const auto top = right / aspect;
    const auto left = -right;
    const auto bottom = -top;
    const auto c = syncDist / zNear;

    // Set ortho matrix
    ortho(c*left, c*right, c*bottom, c*top, zNear, zFar);
}

void Camera::perspectiveFromOrthographic(float, float right, float, float top, float zNear, float zFar, float syncDist)
{
    // Compute perspective projection params
    const auto c = zNear / syncDist;
    const auto r = c*right;
    const auto t = c*top;
    const auto fovY = glm::atan(r / zNear) * 2.f; //assuming right = -left and bottom = -top
    const auto aspect = (2.f * r) / (2.f * t);

    // Set perspective matrix
    perspective(fovY, aspect, zNear, zFar);
}

glm::vec3 Camera::eyeFromViewMatrix() const
{
    const auto eye = viewInvertedMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    return glm::vec3(eye) / eye.w;
}

void Camera::update() const
{
    invalidateMatrices();

    const_cast<Camera*>(this)->changed();
}

void Camera::changed()
{
    invalidated();
}

void Camera::invalidateMatrices() const
{
    m_viewInvertedMatrix.invalidate();
    m_projectionInvertedMatrix.invalidate();
    m_viewProjectionMatrix.invalidate();
    m_viewProjectionInvertedMatrix.invalidate();
    m_normalMatrix.invalidate();
}


} // namespace rendercore
