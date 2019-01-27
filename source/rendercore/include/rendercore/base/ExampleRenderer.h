
#pragma once


#include <memory>

#include <globjects/Program.h>
#include <globjects/Shader.h>
#include <globjects/Texture.h>

#include <rendercore/base/Renderer.h>

#include <rendercore/rendering/Camera.h>
#include <rendercore/rendering/AbstractDrawable.h>


namespace rendercore
{


class ExampleRenderer;


/**
*  @brief
*    Example renderer that displays a spinning object
*/
class RENDERCORE_API ExampleRenderer : public Renderer
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] environment
    *    Environment to which the renderer belongs (must NOT be null!)
    */
    ExampleRenderer(Environment * environment);

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
    virtual void onContextInit(AbstractGLContext * context) override;
    virtual void onContextDeinit(AbstractGLContext * context) override;
    virtual void onRender() override;

protected:
    std::unique_ptr<rendercore::Camera>           m_camera;     ///< Camera in the scene
    std::unique_ptr<rendercore::AbstractDrawable> m_geometry;   ///< Geometry that is rasterized
    std::unique_ptr<globjects::Texture>           m_texture;    ///< Texture
    std::unique_ptr<globjects::Program>           m_program;    ///< Program used for rendering
    std::unique_ptr<globjects::Shader>            m_vertShader; ///< Vertex shader
    std::unique_ptr<globjects::Shader>            m_fragShader; ///< Fragment shader
};


} // namespace rendercore
