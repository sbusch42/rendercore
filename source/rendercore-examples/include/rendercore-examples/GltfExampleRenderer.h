
#pragma once


#include <memory>
#include <vector>

#include <rendercore/Camera.h>
#include <rendercore/Renderer.h>
#include <rendercore/Transform.h>
#include <rendercore/scene/Scene.h>

#include <rendercore-opengl/Mesh.h>
#include <rendercore-opengl/Material.h>
#include <rendercore-opengl/Texture.h>
#include <rendercore-opengl/SceneRenderer.h>

#include <rendercore-examples/rendercore-examples_api.h>


namespace rendercore
{
namespace examples
{


/**
*  @brief
*    Example renderer that displays a GTLF mesh
*/
class RENDERCORE_EXAMPLES_API GltfExampleRenderer : public Renderer
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    GltfExampleRenderer(GpuContainer * container = nullptr);

    // Copying a renderer is not allowed
    GltfExampleRenderer(const GltfExampleRenderer &) = delete;

    // Copying a renderer is not allowed
    GltfExampleRenderer & operator=(const GltfExampleRenderer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~GltfExampleRenderer();

protected:
    virtual void onUpdate() override;
    virtual void onRender() override;

protected:
    // Simulation data
    unsigned int m_counter;   ///< Update counter
    float        m_angle;     ///< Rotation angle
    Transform    m_transform; ///< Transformation of the model

    // GPU data
    std::unique_ptr<rendercore::Camera>                          m_camera;    ///< Camera in the scene
    std::vector< std::unique_ptr<rendercore::opengl::Texture> >  m_textures;  ///< List of textures
    std::vector< std::unique_ptr<rendercore::opengl::Material> > m_materials; ///< List of materials
    std::vector< std::unique_ptr<rendercore::opengl::Mesh> >     m_meshes;    ///< List of meshes
    std::vector< std::unique_ptr<rendercore::Scene> >            m_scenes;    ///< List of scenes

    // Sub-renderers
    std::unique_ptr<rendercore::opengl::SceneRenderer> m_sceneRenderer; ///< Scene renderer
};


} // namespace examples
} // namespace rendercore
