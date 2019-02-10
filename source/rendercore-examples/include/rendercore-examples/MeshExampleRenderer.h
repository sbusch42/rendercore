
#pragma once


#include <memory>

#include <rendercore/Camera.h>
#include <rendercore/Renderer.h>
#include <rendercore/Transform.h>

#include <rendercore-opengl/Mesh.h>
#include <rendercore-opengl/Material.h>
#include <rendercore-opengl/Texture.h>
#include <rendercore-opengl/MeshRenderer.h>

#include <rendercore-examples/rendercore-examples_api.h>


namespace rendercore
{
namespace examples
{


/**
*  @brief
*    Example renderer that displays a spinning mesh
*/
class RENDERCORE_EXAMPLES_API MeshExampleRenderer : public Renderer
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    MeshExampleRenderer(GpuContainer * container = nullptr);

    // Copying a renderer is not allowed
    MeshExampleRenderer(const MeshExampleRenderer &) = delete;

    // Copying a renderer is not allowed
    MeshExampleRenderer & operator=(const MeshExampleRenderer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~MeshExampleRenderer();

protected:
    virtual void onInit() override;
    virtual void onDeinit() override;
    virtual void onUpdate() override;
    virtual void onRender() override;

protected:
    // Simulation data
    unsigned int m_counter;   ///< Update counter
    float        m_angle;     ///< Rotation angle
    Transform    m_transform; ///< Transformation of the model

    // GPU data
    std::unique_ptr<rendercore::Camera>           m_camera;   ///< Camera in the scene
    std::unique_ptr<rendercore::opengl::Mesh>     m_mesh;     ///< Mesh that is rasterized
    std::unique_ptr<rendercore::opengl::Material> m_material; ///< Material
    std::unique_ptr<rendercore::opengl::Texture>  m_texture;  ///< Texture

    // Sub-renderers
    std::unique_ptr<rendercore::opengl::MeshRenderer> m_meshRenderer; ///< Mesh renderer
};


} // namespace examples
} // namespace rendercore
