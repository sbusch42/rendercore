
#include <rendercore/base/Canvas.h>

#include <functional>
#include <algorithm>

#include <glm/glm.hpp>

#include <cppassist/logging/logging.h>
#include <cppassist/memory/make_unique.h>
#include <cppassist/string/manipulation.h>

#include <glbinding/gl/enum.h>

#include <globjects/Framebuffer.h>

#include <rendercore/base/Environment.h>
#include <rendercore/base/Renderer.h>


namespace rendercore
{


Canvas::Canvas(Environment * environment)
: m_environment(environment)
, m_openGLContext(nullptr)
, m_initialized(false)
, m_timeDelta(0.0f)
, m_rendered(false)
, m_renderer(nullptr)
, m_oldRenderer(nullptr)
, m_replaceRenderer(false)
{
}

Canvas::~Canvas()
{
}

const Environment * Canvas::environment() const
{
    return m_environment;
}

Environment * Canvas::environment()
{
    return m_environment;
}

const AbstractGLContext * Canvas::openGLContext() const
{
    return m_openGLContext;
}

AbstractGLContext * Canvas::openGLContext()
{
    return m_openGLContext;
}

void Canvas::setOpenGLContext(AbstractGLContext * context)
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);

    // Deinitialize renderer in old context
    if (m_openGLContext)
    {
        cppassist::debug(2, "rendercore") << "deinitContext()";

        if (m_renderer)
        {
            m_renderer->deinitContext(m_openGLContext);
        }

        m_openGLContext = nullptr;
    }

    // Initialize renderer in new context
    if (context)
    {
        cppassist::debug(2, "rendercore") << "initContext()";

        m_openGLContext = context;

        // Initialization happens later during render
        /*
        if (m_renderer)
        {
            m_renderer->initContext(m_openGLContext);
        }
        */
        m_replaceRenderer = true;
    }

    // Reset status
    m_initialized = false;
}

void Canvas::setRenderer(Renderer * renderer)
{
    m_renderer = renderer;
}

void Canvas::updateTime()
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);

    // In multithreaded viewers, updateTime() might get called several times
    // before render(). Therefore, the time delta is accumulated until the
    // pipeline is actually rendered, and then reset by the method render().

    // Get number of milliseconds since last call
    auto duration = m_clock.elapsed();
    m_clock.reset();

    // Determine time delta and virtual time
    float timeDelta = std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
    m_timeDelta += timeDelta;

    if (!m_renderer)
    {
        return;
    }

    // Update timing
    m_renderer->setTimeDelta(m_timeDelta);

    // Check if a redraw is required
    checkRedraw();
}

void Canvas::setViewport(const glm::vec4 & deviceViewport)
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);

    // Store viewport information
    m_viewport  = deviceViewport;
    m_initialized = true;

    if (!m_renderer)
    {
        return;
    }

    // Promote new viewport
    m_renderer->setViewport(m_viewport);

    // Check if a redraw is required
    checkRedraw();
}

const glm::vec4 & Canvas::viewport() const
{
    return m_viewport;
}

void Canvas::render(globjects::Framebuffer * targetFBO)
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);

    // Reset time delta
    m_timeDelta = 0.0f;

    auto fboName = targetFBO->hasName() ? targetFBO->name() : std::to_string(targetFBO->id());
    cppassist::debug(2, "rendercore") << "render(); " << "targetFBO: " << fboName;

    // Abort if not initialized
    if (!m_initialized || !m_renderer)
    {
        return;
    }

    // Check if the renderer is to be replaced
    if (m_replaceRenderer)
    {
        // Check if an old renderer must be destroyed
        if (m_oldRenderer)
        {
            // Deinitialize old renderer
            m_oldRenderer->deinitContext(m_openGLContext);

            // Destroy old renderer
            m_oldRenderer = nullptr;
        }

        // Initialize renderer
        m_renderer->initContext(m_openGLContext);

        // Promote viewport information
        m_renderer->setViewport(m_viewport);

        // Replace finished
        m_replaceRenderer = false;
    }

    // Render
    m_renderer->render();

    // Signal that a frame has been rendered
    m_rendered = true;
}

void Canvas::checkRedraw()
{
    // Invoke callbacks after a frame has been rendered
    if (m_rendered) {
        // Reset flag
        m_rendered = false;
    }

    if (!m_renderer)
    {
        return;
    }

    bool redraw = false;

    if (redraw)
    {
        this->redraw();
    }
}


} // namespace rendercore
