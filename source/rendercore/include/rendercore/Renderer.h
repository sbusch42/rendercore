
#pragma once


#include <glm/vec4.hpp>

#include <rendercore/GpuContainer.h>


namespace rendercore
{


/**
*  @brief
*    Base class for rendering
*
*    A renderer is a class that does the actual rendering. It can be attached
*    to a canvas, into which it will then render. It is not possible to attach
*    the same renderer to more than one canvas at a time, because different
*    canvases can have different rendering contexts.
*
*    There are two important functions on a renderer: update and render.
*
*    The update function allows a renderer to "think", e.g., to update its
*    simulation or animation processes. Therefore, its onUpdate-method is
*    called, in which the simulation can be implemented. This function is
*    executed solely on the CPU, no rendering context is active, so don't call
*    or use any GPU functions in this context. An update is triggered once,
*    so if a simulation needs to be update continuously, the renderer must
*    call scheduleUpdate() in onUpdate to schedule an update for the next frame.
*    If as a result of the update, a new frame must be drawn, the renderer
*    should call redraw(), then the rendering of a frame will be scheduled
*    right after the update.
*
*    Whenever the canvas needs a redraw, e.g., if the window has been resized
*    or otherwise needs to be redrawn, it will call the render-function of the
*    renderer. But also the renderer can trigger a redraw, if it decides that
*    it needs to be redrawn, by calling scheduleRedraw(). The canvas will
*    then issue a redraw.
*/
class RENDERCORE_API Renderer : public GpuContainer
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (must NOT be null!)
    */
    Renderer(GpuContainer * container);

    // Copying a renderer is not allowed
    Renderer(const Renderer &) = delete;

    // Copying a renderer is not allowed
    Renderer & operator=(const Renderer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Renderer();

    /**
    *  @brief
    *    Get viewport for rendering
    *
    *  @return
    *    Viewport in device coordinates (x, y, w, h)
    */
    glm::vec4 viewport() const;

    /**
    *  @brief
    *    Set viewport for rendering
    *
    *  @param[in] viewport
    *    Viewport in device coordinates (x, y, w, h)
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
    *    Set time delta since last update
    *
    *  @param[in] timeDelta
    *    Time delta (in seconds)
    */
    void setTimeDelta(float timeDelta);

    /**
    *  @brief
    *    Check if renderer needs to be updated
    *
    *  @return
    *    'true' if renderer needs to be updated, else 'false'
    *
    *  @see update
    */
    bool needsUpdate() const;

    /**
    *  @brief
    *    Schedule update on renderer
    *
    *  @see update
    *
    *  @remarks
    *    Call this function will ensure that an update will be issued
    *    in the next main loop iteration. Note however that onUpdate()
    *    may not *only* be called after you used scheduleUpdate(), it
    *    will also be called automatically whenever one or more events
    *    on the main loop have been processed. This ensures that the
    *    update process will not fall to a permanent halt, event if
    *    some messages are lost.
    */
    void scheduleUpdate();

    /**
    *  @brief
    *    Update (handle animation etc.)
    *
    *  @remarks
    *    When the renderer is updated, its onUpdate-method is called.
    *    In this method, all updates to its simulation or animation
    *    take place. This only updates the simulation, it does not
    *    automatically redraw the renderer.
    *
    *  @see onUpdate
    */
    void update();

    /**
    *  @brief
    *    Check if renderer needs to be executed
    *
    *  @return
    *    'true' if renderer needs to be executed, else 'false'
    *
    *  @see render
    */
    bool needsRedraw() const;

    /**
    *  @brief
    *    Schedule redraw on renderer
    *
    *  @see render
    *
    *  @remarks
    *    Will in most UI backends also trigger an update.
    *    But if you want to make sure that an update happens,
    *    call scheduleUpdate() as well.
    */
    void scheduleRedraw();

    /**
    *  @brief
    *    Execute rendering
    *
    *  @remarks
    *    When the renderer is redrawn, its onRender-method is called.
    *    In this method, the rendering code must be executed to
    *    produce a new frame for the output.
    *
    *  @notes
    *    - Requires an active rendering context
    *
    *  @see onRender
    */
    void render();

protected:
    /**
    *  @brief
    *    Called when the renderer is updated
    *
    *  @remarks
    *    During update, the renderer executes its simulation or animation.
    *    Read m_timeDelta to determine the time that has passed since the
    *    last call to onUpdate(). It should be used to advance the simulation.
    *    Do not use any GPU function or objects in this function, as no
    *    rendering context is active. To schedule a redraw as a result of
    *    the update, call scheduleRedraw(). To continuously update the
    *    simulation, call scheduleUpdate(). Keep in minde that onUpdate()
    *    may be called an arbitrary number of times, and not only when
    *    you scheduled an update. So implement this function to always use
    *    m_timeDelta to determine the amount of time that has passed since
    *    the last call, and also expect m_timeDelta to be very small.
    */
    virtual void onUpdate();

    /**
    *  @brief
    *    Called when the renderer is redrawn
    *
    *  @remarks
    *    This function is called to produce exactly one frame for the output.
    *    Use m_viewport to set the viewport for rendering into the currently
    *    set canvas.
    */
    virtual void onRender();

protected:
    glm::vec4 m_viewport;    ///< Viewport in device coordinates (x, y, w, h)
    float     m_timeDelta;   ///< Time delta (in seconds)
    bool      m_needsUpdate; ///< Is an update needed?
    bool      m_needsRedraw; ///< Is a redraw needed?
};


} // namespace rendercore
