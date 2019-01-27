
#pragma once


#include <array>

#include <glm/vec4.hpp>

#include <rendercore/rendercore_api.h>


namespace rendercore
{


class AbstractContext;
class Environment;


/**
*  @brief
*    Base class for rendering
*
*    A renderer is a class that does the actual rendering. It can be attached
*    to a canvas, into which it will then render. It is not possible to attach
*    the same renderer to more than one canvas at a time, because different
*    canvases can use different rendering contexts.
*
*    Whenever the canvas needs a redraw, e.g., if the window has been resized
*    or otherwise needs to be redrawn, it will call the render-function of the
*    renderer. But also the renderer can trigger a redraw, if it decides that
*    it needs to be redrawn, by invoking its redraw-signal. The canvas will
*    then issue a redraw.
*/
class RENDERCORE_API Renderer
{
public:
    //@{
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] environment
    *    Environment to which the renderer belongs (must NOT be null!)
    */
    Renderer(Environment * environment);

    // Copying a renderer is not allowed
    Renderer(const Renderer &) = delete;

    // Copying a renderer is not allowed
    Renderer & operator=(const Renderer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Renderer();
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
    *    Get rendering context
    *
    *  @return
    *    Rendering context used for rendering (can be null)
    */
    const AbstractContext * context() const;
    AbstractContext * context();
    //@}

    /**
    *  @brief
    *    Initialize in rendering context
    *
    *  @param[in] context
    *    Rendering context used for rendering (must NOT null!)
    *
    *  @see onContextInit
    */
    void initContext(AbstractContext * context);

    /**
    *  @brief
    *    De-Initialize in rendering context
    *
    *  @param[in] context
    *    Rendering context used for rendering (must NOT null!)
    *
    *  @see onContextDeinit
    */
    void deinitContext(AbstractContext * context);

    /**
    *  @brief
    *    Execute rendering
    *
    *  @see onRender
    */
    void render();

    /**
    *  @brief
    *    Check if renderer needs to be executed
    *
    *  @return
    *    'true' if renderer needs to be executed, else 'false'
    */
    bool needsRedraw() const;

    void setViewport(const glm::vec4 & viewport);
    void setTimeDelta(float timeDelta);

protected:
    virtual void onContextInit(AbstractContext * context);
    virtual void onContextDeinit(AbstractContext * context);
    virtual void onRender();

protected:
    Environment       * m_environment;        ///< Environment to which the renderer belongs
    AbstractContext   * m_context;            ///< Rendering context used for rendering
    glm::vec4           m_viewport;           ///< Viewport in device coordinates (x, y, w, h)
    float               m_timeDelta;          ///< Time delta (in seconds)
    bool                m_timeMeasurement;    ///< Status of time measurements for CPU and GPU
    bool                m_resultAvailable;    ///< Flag indicating whether a measurement from previous frames is available for report
    bool                m_useQueryPairOne;    ///< Flag indicating which queries are currently used
    uint64_t            m_lastCPUDuration;    ///< Time spent in onRender last frame (in nanoseconds)
    uint64_t            m_currentCPUDuration; ///< Time spent in onRender current frame (in nanoseconds)
    uint64_t            m_lastGPUDuration;    ///< Time for GPU commands issued during onRender (in nanoseconds)

    std::array<unsigned int, 4> m_queries; ///< OpenGL query objects (front/back; start/end)
};


} // namespace rendercore
