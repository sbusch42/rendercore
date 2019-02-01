
#pragma once


#include <memory>
#include <mutex>

#include <glm/vec4.hpp>

#include <rendercore/Cached.h>
#include <rendercore/Signal.h>
#include <rendercore/ChronoTimer.h>


namespace rendercore
{


class Environment;
class AbstractContext;
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
    Signal<> wakeup; ///< Use this to wakeup the main loop to resume continuous simulation or redraw

public:
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

    /**
    *  @brief
    *    Get environment
    *
    *  @return
    *    Environment to which the canvas belongs (never null)
    */
    const Environment * environment() const;

    /**
    *  @brief
    *    Get environment
    *
    *  @return
    *    Environment to which the canvas belongs (never null)
    */
    Environment * environment();

    /**
    *  @brief
    *    Get rendering context
    *
    *  @return
    *    Rendering context used for rendering on the canvas (can be null)
    *
    *  @remarks
    *    The returned context can be null if the canvas has not been
    *    initialized yet, or the method is called between deinitContext()
    *    and initContext() when the context has been changed.
    *    Aside from that, there should always be a valid rendering context
    *    attached to the canvas.
    */
    const AbstractContext * context() const;

    /**
    *  @brief
    *    Get rendering context
    *
    *  @return
    *    Rendering context used for rendering on the canvas (can be null)
    *
    *  @remarks
    *    The returned context can be null if the canvas has not been
    *    initialized yet, or the method is called between deinitContext()
    *    and initContext() when the context has been changed.
    *    Aside from that, there should always be a valid rendering context
    *    attached to the canvas.
    */
    AbstractContext * context();

    /**
    *  @brief
    *    Initialize in rendering context
    *
    *  @param[in] context
    *    Rendering context used for rendering on the canvas (must NOT be null)
    *
    *  @remarks
    *    This function needs to be called by the windowing backend after
    *    a new context has been created. The context must already be
    *    active when this function is called. If the canvas has been
    *    used in another context previously, it must first be deinitialized
    *    in that context using contextDeinit(), before calling this
    *    function. If another context is still set for this canvas,
    *    the function will fail with an error.
    */
    void initContext(AbstractContext * context);

    /**
    *  @brief
    *    De-initialize in rendering context
    *
    *  @param[in] context
    *    Rendering context used for rendering on the canvas (must NOT be null)
    *
    *  @remarks
    *    This function needs to be called by the windowing backend
    *    before a context is destroyed or a new one is set for the canvas.
    *    The context must be active when this function is called.
    *    If the canvas has not been initialized for this context,
    *    the function will fail with an error.
    */
    void deinitContext(AbstractContext * context);

    /**
    *  @brief
    *    Set renderer
    *
    *  @param[in] renderer
    *    Renderer to use
    *
    *  @remarks
    *    Will replace the previous renderer attach to the canvas.
    *    The canvas takes over ownership over the renderer.
    */
    void setRenderer(std::unique_ptr<Renderer> && renderer);

    /**
    *  @brief
    *    Get viewport
    *
    *  @return
    *    Viewport (in real device coordinates)
    */
    glm::vec4 viewport() const;

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
    *    Get time delta since last update
    *
    *  @return
    *    Time delta (in seconds)
    */
    float timeDelta() const;

    /**
    *  @brief
    *    Update virtual time (must be called from UI thread)
    *
    *  @remarks
    *    This function determines the time delta since the last call to
    *    this function and passes it on to the renderer to allow for
    *    continuous updates of the simulation. If this function is
    *    called multiple times, the time delta is accumulated until
    *    update() is finally called. That will reset the time delta to 0.
    */
    void updateTime();

    /**
    *  @brief
    *    Check if canvas needs to be updated
    *
    *  @return
    *    'true' if canvas needs to be updated, else 'false'
    *
    *  @see update
    */
    bool needsUpdate() const;

    /**
    *  @brief
    *    Schedule update on canvas
    *
    *  @see update
    */
    void scheduleUpdate();

    /**
    *  @brief
    *    Update the simulation (must be called from UI thread)
    *
    *  @remarks
    *    This will call update on the renderer and then reset
    *    the time delta to 0.
    */
    void update();

    /**
    *  @brief
    *    Check if canvas needs to be executed
    *
    *  @return
    *    'true' if canvas needs to be executed, else 'false'
    *
    *  @see render
    */
    bool needsRedraw() const;

    /**
    *  @brief
    *    Schedule redraw on canvas
    *
    *  @see render
    */
    void scheduleRedraw();

    /**
    *  @brief
    *    Perform rendering (must be called from render thread)
    *
    *  @remarks
    *    This will call render on the renderer.
    */
    void render();

protected:
    Environment               * m_environment;   ///< Environment to which the canvas belongs
    AbstractContext           * m_context;       ///< Rendering context used for rendering onto the canvas
    std::unique_ptr<Renderer>   m_renderer;      ///< Renderer that renders into the canvas
    std::unique_ptr<Renderer>   m_newRenderer;   ///< Renderer that is scheduled to replace the current renderer
    Cached<glm::vec4>           m_viewport;      ///< Viewport (in real device coordinates)
    float                       m_timeDelta;     ///< Time delta since the last update (in seconds)
    ChronoTimer                 m_clock;         ///< Time measurement
    std::recursive_mutex        m_mutex;         ///< Mutex for separating main and render thread
};


} // namespace rendercore
