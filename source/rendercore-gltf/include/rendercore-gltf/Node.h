
#pragma once


#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Node
*/
class RENDERCORE_GLTF_API Node
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Node();

    /**
    *  @brief
    *    Destructor
    */
    ~Node();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Node name
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Set name
    *
    *  @param[in] name
    *    Node name
    */
    void setName(const std::string & name);

    /**
    *  @brief
    *    Check if transformation matrix has been set
    *
    *  @return
    *    'true' if matrix has been set, else 'false'
    */
    bool hasMatrix() const;

    /**
    *  @brief
    *    Get transformation matrix
    *
    *  @return
    *    Transformation matrix
    */
    glm::mat4 matrix() const;

    /**
    *  @brief
    *    Set transformation matrix
    *
    *  @param[in] matrix
    *    Transformation matrix
    */
    void setMatrix(const glm::mat4 & matrix);

    /**
    *  @brief
    *    Get translation
    *
    *  @return
    *    Translation
    */
    glm::vec3 translation() const;

    /**
    *  @brief
    *    Set translation
    *
    *  @param[in] translation
    *    Translation
    */
    void setTranslation(const glm::vec3 & translation);

    /**
    *  @brief
    *    Get rotation
    *
    *  @return
    *    Rotation
    */
    glm::vec4 rotation() const;

    /**
    *  @brief
    *    Set rotation
    *
    *  @param[in] rotation
    *    Rotation
    */
    void setRotation(const glm::vec4 & rotation);

    /**
    *  @brief
    *    Get scale
    *
    *  @return
    *    Scale
    */
    glm::vec3 scale() const;

    /**
    *  @brief
    *    Set scale
    *
    *  @param[in] scale
    *    Scale
    */
    void setScale(const glm::vec3 & scale);

    /**
    *  @brief
    *    Get children
    *
    *  @return
    *    Indices of child nodes
    */
    const std::vector<unsigned int> & children() const;

    /**
    *  @brief
    *    Set children
    *
    *  @param[in] children
    *    Indices of child nodes
    */
    void setChildren(const std::vector<unsigned int> & children);

    /**
    *  @brief
    *    Get attached camera
    *
    *  @return
    *    Index of attached camera (-1 for none)
    */
    int camera() const;

    /**
    *  @brief
    *    Get attached camera
    *
    *  @param[in] camera
    *    Index of attached camera (-1 for none)
    */
    void setCamera(int camera);

    /**
    *  @brief
    *    Get attached mesh
    *
    *  @return
    *    Index of attached mesh (-1 for none)
    */
    int mesh() const;

    /**
    *  @brief
    *    Get attached mesh
    *
    *  @param[in] mesh
    *    Index of attached mesh (-1 for none)
    */
    void setMesh(int mesh);

protected:
    std::string               m_name;        ///< Node name
    int                       m_camera;      ///< Index of attached camera
    int                       m_mesh;        ///< Index of attached mesh
    bool                      m_hasMatrix;   ///< 'true' if matrix has been set, else 'false'
    glm::mat4                 m_matrix;      ///< Transformation matrix
    glm::vec3                 m_translation; ///< Translation
    glm::vec4                 m_rotation;    ///< Rotation quaternion
    glm::vec3                 m_scale;       ///< Scale
    std::vector<unsigned int> m_children;    ///< Indices of child nodes
};


} // namespace gltf
} // namespace rendercore
