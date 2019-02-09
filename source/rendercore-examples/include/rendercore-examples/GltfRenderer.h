
#pragma once


#include <memory>

#include <rendercore/Camera.h>
#include <rendercore/Renderer.h>
#include <rendercore/Transform.h>

#include <rendercore-opengl/Geometry.h>
#include <rendercore-opengl/Program.h>

#include <rendercore-examples/rendercore-examples_api.h>


namespace rendercore
{
namespace examples
{


/**
*  @brief
*    Example renderer that displays a GTLF mesh
*/
class RENDERCORE_EXAMPLES_API GltfRenderer : public Renderer
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    GltfRenderer(GpuContainer * container = nullptr);

    // Copying a renderer is not allowed
    GltfRenderer(const GltfRenderer &) = delete;

    // Copying a renderer is not allowed
    GltfRenderer & operator=(const GltfRenderer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~GltfRenderer();

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
    std::unique_ptr<rendercore::opengl::Geometry> m_geometry; ///< Geometry that is rasterized
    std::unique_ptr<rendercore::opengl::Program>  m_program;  ///< Program used for rendering
};


} // namespace examples
} // namespace rendercore
