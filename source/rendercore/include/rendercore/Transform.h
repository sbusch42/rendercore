
#pragma once


#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <rendercore/Cached.h>


namespace rendercore
{


/**
*  @brief
*    Representation of a 3D transformation (translation, rotation, and scale)
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
    *    Get rotation
    *
    *  @return
    *    Rotation quaternion
    */
    const glm::quat & rotation() const;

    /**
    *  @brief
    *    Set rotation
    *
    *  @param[in] rotation
    *    Rotation quaternion
    */
    void setRotation(const glm::quat & rotation);

    /**
    *  @brief
    *    Set rotation
    *
    *  @param[in] rotation
    *    Rotation quaternion
    */
    void setRotation(const glm::vec4 & rotation);

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

    /**
    *  @brief
    *    Set transformation matrix
    *
    *  @param[in] transform
    *    Transformation matrix
    */
    void setTransform(const glm::mat4 & transform);

protected:
    // Transformation components
    glm::quat m_rotation;    ///< Rotation quaternion
    glm::vec3 m_translation; ///< Vector by which the object is translated
    glm::vec3 m_scale;       ///< Factors by which the object is scaled

    // Resulting matrix
    Cached<glm::mat4> m_transform; ///< Transformation matrix
};


} // namespace rendercore
