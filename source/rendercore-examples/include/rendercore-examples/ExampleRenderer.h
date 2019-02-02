
#pragma once


#include <memory>

#include <globjects/Program.h>
#include <globjects/Shader.h>
#include <globjects/Texture.h>

#include <rendercore/AbstractDrawable.h>
#include <rendercore/Camera.h>
#include <rendercore/Renderer.h>
#include <rendercore/Transform.h>

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
    */
    ExampleRenderer();

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
    virtual void onContextInit(AbstractContext * context) override;
    virtual void onContextDeinit(AbstractContext * context) override;
    virtual void onUpdate() override;
    virtual void onRender() override;

protected:
    // Simulation data
    unsigned int m_counter;   ///< Update counter
    Transform    m_transform; ///< Transformation of the model

    // GPU data
    std::unique_ptr<rendercore::Camera>           m_camera;     ///< Camera in the scene
    std::unique_ptr<rendercore::AbstractDrawable> m_geometry;   ///< Geometry that is rasterized
    std::unique_ptr<rendercore::opengl::Texture>  m_texture;    ///< Texture
    std::unique_ptr<globjects::Program>           m_program;    ///< Program used for rendering
    std::unique_ptr<globjects::Shader>            m_vertShader; ///< Vertex shader
    std::unique_ptr<globjects::Shader>            m_fragShader; ///< Fragment shader
};


} // namespace examples
} // namespace rendercore
