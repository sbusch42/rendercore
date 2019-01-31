
#pragma once


#include <glm/glm.hpp>

#include <rendercore/Cached.h>


namespace rendercore
{


/**
*  @brief
*    Represents a 3D transformation (translation, rotation, and scale)
*/
class RENDERCORE_API Transform
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Transform();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Transform();

    /**
    *  @brief
    *    Get rotation axis
    *
    *  @return
    *    Rotation axis
    */
    const glm::vec3 & rotationAxis() const;

    /**
    *  @brief
    *    Set rotation axis
    *
    *  @param[in] axis
    *    Rotation axis
    */
    void setRotationAxis(const glm::vec3 & axis);

    /**
    *  @brief
    *    Get rotation angle
    *
    *  @return
    *    Rotation angle (in radians)
    */
    float rotationAngle() const;

    /**
    *  @brief
    *    Set rotation angle
    *
    *  @param[in] angle
    *    Rotation angle (in radians)
    */
    void setRotationAngle(float angle);

    /**
    *  @brief
    *    Get translation
    *
    *  @return
    *    Translation (x, y, z)
    */
    const glm::vec3 & translation() const;

    /**
    *  @brief
    *    Set translation
    *
    *  @param[in] translation
    *    Translation (x, y, z)
    */
    void setTranslation(const glm::vec3 & translation);

    /**
    *  @brief
    *    Get scale
    *
    *  @return
    *    Scale (x, y, z)
    */
    const glm::vec3 & scale() const;

    /**
    *  @brief
    *    Set scale
    *
    *  @param[in] scale
    *    Scale (x, y, z)
    */
    void setScale(const glm::vec3 & scale);

    /**
    *  @brief
    *    Get transformation matrix
    *
    *  @return
    *    Transformation matrix
    */
    const glm::mat4 & transform() const;

protected:
    // Transformation components
    glm::vec3 m_rotationAxis;  ///< Axis around which the object is rotated
    float     m_rotationAngle; ///< Rotation angle (in radians)
    glm::vec3 m_translation;   ///< Vector by which the object is translated
    glm::vec3 m_scale;         ///< Factors by which the object is scaled

    // Resulting matrix
    Cached<glm::mat4> m_transform; ///< Transformation matrix
};


} // namespace rendercore
