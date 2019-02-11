
#pragma once


#include <rendercore/GpuContainer.h>

#include <glm/glm.hpp>

#include <rendercore-opengl/Program.h>


namespace rendercore
{


class Camera;
class Scene;
class SceneNode;
class Transform;


namespace opengl
{


class Mesh;


/**
*  @brief
*    Scene renderer
*/
class RENDERCORE_OPENGL_API SceneRenderer : public GpuContainer
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (must NOT be null!)
    */
    SceneRenderer(GpuContainer * container);

    // Copying a renderer is not allowed
    SceneRenderer(const SceneRenderer &) = delete;

    // Copying a renderer is not allowed
    SceneRenderer & operator=(const SceneRenderer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~SceneRenderer();

    /**
    *  @brief
    *    Render scene
    *
    *  @param[in] scene
    *    Scene to render
    *  @param[in] transform
    *    Transformation
    *  @param[in] camera
    *    Camera (can be null)
    */
    void render(Scene & scene, const glm::mat4 & transform, Camera * camera);

    /**
    *  @brief
    *    Render scene node
    *
    *  @param[in] node
    *    Scene node to render
    *  @param[in] transform
    *    Transformation
    *  @param[in] camera
    *    Camera (can be null)
    */
    void render(SceneNode & node, const glm::mat4 & transform, Camera * camera);

    /**
    *  @brief
    *    Render mesh
    *
    *  @param[in] mesh
    *    Mesh to render
    *  @param[in] transform
    *    Model transformation
    *  @param[in] camera
    *    Camera (can be null)
    */
    void render(Mesh & mesh, const glm::mat4 & transform, Camera * camera);

protected:
    // GPU data
    std::unique_ptr<rendercore::opengl::Program>  m_program;  ///< Program used for rendering
};


} // namespace opengl
} // namespace rendercore
