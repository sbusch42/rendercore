
#pragma once


#include <memory>

#include <rendercore/Camera.h>
#include <rendercore/Renderer.h>
#include <rendercore/Transform.h>

#include <rendercore-opengl/Program.h>
#include <rendercore-opengl/Texture.h>
#include <rendercore-opengl/Mesh.h>

#include <rendercore-examples/rendercore-examples_api.h>


namespace rendercore
{
namespace examples
{


/**
*  @brief
*    Example renderer that displays different kinds of geometry
*/
class RENDERCORE_EXAMPLES_API GeometryRenderer : public Renderer
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    GeometryRenderer(GpuContainer * container = nullptr);

    // Copying a renderer is not allowed
    GeometryRenderer(const GeometryRenderer &) = delete;

    // Copying a renderer is not allowed
    GeometryRenderer & operator=(const GeometryRenderer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~GeometryRenderer();

protected:
    // Geometry generation
    void createPoints();
    void createPointsInterleaved();

    // Virtual Renderer functions
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
    std::unique_ptr<rendercore::opengl::Mesh>     m_geometry; ///< Geometry that is rasterized
    std::unique_ptr<rendercore::opengl::Texture>  m_texture;  ///< Texture
    std::unique_ptr<rendercore::opengl::Program>  m_program;  ///< Program used for rendering
};


} // namespace examples
} // namespace rendercore
