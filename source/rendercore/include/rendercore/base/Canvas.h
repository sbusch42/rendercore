
#pragma once


#include <mutex>

#include <glm/vec4.hpp>

#include <cppexpose/signal/Signal.h>

#include <rendercore/base/ChronoTimer.h>


namespace globjects
{
    class Framebuffer;
}


namespace rendercore
{


class Environment;
class AbstractGLContext;
class Renderer;


/**
*  @brief
*    Representation of a canvas onto which can be rendered
*
*    A canvas is attached to a window or offscreen context and handles the
*    actual rendering. It should be embedded by the windowing backend and
*    receives state changes from the outside (such as window size, mouse,
*    or keyboard events) and passes them on to the rendering components.
*/
class RENDERCORE_API Canvas
{
public:
    // Must be emitted only from the UI thread
    cppexpose::Signal<> redraw; ///< Called when the canvas needs to be redrawn

public:
    //@{
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] environment
    *    Environment to which the canvas belongs (must NOT be null!)
    */
    Canvas(Environment * environment);

    /**
    *  @brief
    *    Destructor
    */
    ~Canvas();
    //@}

    //@{
    /**
    *  @brief
    *    Get environment
    *
    *  @return
    *    Environment to which the canvas belongs (never null)
    */
    const Environment * environment() const;
    Environment * environment();
    //@}

    //@{
    /**
    *  @brief
    *    Get OpenGL context
    *
    *  @return
    *    OpenGL context used for rendering on the canvas (can be null)
    *
    *  @remarks
    *    The returned context can be null if the canvas has not been
    *    initialized yet, or the method is called between onContextDeinit()
    *    and onContextInit() when the context has been changed.
    *    Aside from that, there should always be a valid OpenGL context
    *    attached to the canvas.
    */
    const AbstractGLContext * openGLContext() const;
    AbstractGLContext * openGLContext();
    //@}

    //@{
    /**
    *  @brief
    *    Set OpenGL context
    *
    *  @param[in] context
    *    OpenGL context used for rendering on the canvas (can be null)
    *
    *  @remarks
    *    This function should only be called by the windowing backend.
    *    If the canvas still has a valid context, onContextDeinit()
    *    will be called and the context pointer will be set to nullptr.
    *    Then, if the new context is valid, the context pointer will be
    *    set to that new context and onContextInit() will be invoked.
    */
    void setOpenGLContext(AbstractGLContext * context);

    /**
    *  @brief
    *    Set renderer
    *
    *  @param[in] renderer
    *    Renderer to use
    */
    void setRenderer(Renderer * renderer);

    /**
    *  @brief
    *    Update virtual time (must be called from UI thread)
    *
    *  @remarks
    *    This function determines the time delta since the last call to
    *    the function and updates the internal virtual time. This is
    *    passed on to the renderer to allow for continuous updates
    *    of the virtual scene. If a pipeline depends on the virtual time
    *    or time delta inputs and in turn invalidates its render outputs,
    *    a redraw will be scheduled. Otherwise, only the virtual time is
    *    updated regularly, but no redraw occurs.
    */
    void updateTime();

    /**
    *  @brief
    *    Set viewport (must be called from UI thread)
    *
    *  @param[in] viewport
    *    Viewport (in real device coordinates)
    */
    void setViewport(const glm::vec4 & viewport);

    /**
    *  @brief
    *    Get viewport (in real device coordinates)
    *
    *  @return
    *    The viewport
    */
    const glm::vec4 & viewport() const;

    /**
    *  @brief
    *    Perform rendering (must be called from render thread)
    *
    *  @param[in] targetFBO
    *    Framebuffer into which is rendered
    */
    void render(globjects::Framebuffer * targetFBO);
    //@}

protected:
    //@{
    /**
    *  @brief
    *    Check if a redraw is required
    *
    *  @remarks
    *    This function checks if the renderer needs to be redrawn
    *    and invokes the redraw signal if that is the case.
    */
    void checkRedraw();
    //@}

protected:
    Environment          * m_environment;   ///< Environment to which the canvas belongs
    AbstractGLContext    * m_openGLContext; ///< OpenGL context used for rendering onto the canvas
    bool                   m_initialized;   ///< 'true' if the context has been initialized and the viewport has been set, else 'false'
    ChronoTimer            m_clock;         ///< Time measurement
    glm::vec4              m_viewport;      ///< Viewport (in real device coordinates)
    float                  m_timeDelta;     ///< Time delta since the last update (in seconds)
    std::recursive_mutex   m_mutex;         ///< Mutex for separating main and render thread
    bool                   m_rendered;      ///< 'true' after a new frame has been drawn
    Renderer             * m_renderer;      ///< Renderer that renders into the canvas
    Renderer             * m_oldRenderer;
    bool                   m_replaceRenderer;
};


} // namespace rendercore
