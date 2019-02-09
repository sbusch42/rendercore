
#pragma once


#include <memory>

#include <rendercore/AbstractDrawable.h>
#include <rendercore/Camera.h>
#include <rendercore/Renderer.h>
#include <rendercore/Transform.h>

#include <rendercore-opengl/Program.h>
#include <rendercore-opengl/Texture.h>

#include <rendercore-examples/rendercore-examples_api.h>


namespace rendercore
{
namespace examples
{


/**
*  @brief
*    Example renderer that displays a spinning object
*/
class RENDERCORE_EXAMPLES_API ExampleRenderer : public Renderer
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    ExampleRenderer(GpuContainer * container = nullptr);

    // Copying a renderer is not allowed
    ExampleRenderer(const ExampleRenderer &) = delete;

    // Copying a renderer is not allowed
    ExampleRenderer & operator=(const ExampleRenderer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ExampleRenderer();

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
    std::unique_ptr<rendercore::AbstractDrawable> m_geometry; ///< Geometry that is rasterized
    std::unique_ptr<rendercore::opengl::Texture>  m_texture;  ///< Texture
    std::unique_ptr<rendercore::opengl::Program>  m_program;  ///< Program used for rendering
};


} // namespace examples
} // namespace rendercore
