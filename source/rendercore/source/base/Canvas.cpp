
#include <rendercore/base/Canvas.h>

#include <cppassist/logging/logging.h>

#include <globjects/Framebuffer.h>

#include <rendercore/base/Environment.h>
#include <rendercore/base/Renderer.h>


namespace rendercore
{


Canvas::Canvas(Environment * environment)
: m_environment(environment)
, m_openGLContext(nullptr)
, m_timeDelta(0.0f)
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

void Canvas::initContext(AbstractGLContext * context)
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);
    cppassist::debug(0, "rendercore") << "Canvas::initContext()";

    // Check if canvas is already attached to this context
    if (m_openGLContext == context) {
        cppassist::error("rendercore") << "Canvas::initContext(): Canvas is already attached to this context.";
        return;
    }

    // Check if canvas is attached to another context
    if (m_openGLContext != nullptr) {
        cppassist::error("rendercore") << "Canvas::initContext(): Canvas is already attached to another context.";
        return;
    }

    // Initialize context
    if (context) {
        // Save context
        m_openGLContext = context;

        // The renderer will be initialized in the new context on the next rendering call
        redraw();
    }
}

void Canvas::deinitContext(AbstractGLContext * context)
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);
    cppassist::debug(0, "rendercore") << "Canvas::deinitContext()";

    // Check if canvas is attached to the context
    if (m_openGLContext != context) {
        cppassist::error("rendercore") << "Canvas::deinitContext(): Canvas is not attached to this context.";
        return;
    }

    // Deinitialize context
    if (m_openGLContext) {
        // Deinitialize renderer in context
        if (m_renderer) {
            m_renderer->deinitContext(m_openGLContext);
        }

        // Reset context
        m_openGLContext = nullptr;
    }

    // Reset viewport
    m_viewport.invalidate();
}

void Canvas::setRenderer(std::unique_ptr<Renderer> && renderer)
{
    // Set new renderer to replace the old one
    m_newRenderer = std::move(renderer);
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

    if (!m_renderer) {
        return;
    }

    // Update timing
    m_renderer->setTimeDelta(m_timeDelta);

    // Check if a redraw is required
    checkRedraw();
}

glm::vec4 Canvas::viewport() const
{
    return m_viewport.value();
}

void Canvas::setViewport(const glm::vec4 & viewport)
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);

    // Store viewport information
    m_viewport = viewport;

    // Promote new viewport
    if (m_renderer) {
        m_renderer->setViewport(m_viewport.value());
    }

    // Check if a redraw is required
    checkRedraw();
}

void Canvas::render(globjects::Framebuffer * targetFBO)
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);

    // Reset time delta
    m_timeDelta = 0.0f;

    auto fboName = targetFBO->hasName() ? targetFBO->name() : std::to_string(targetFBO->id());
    cppassist::debug(0, "rendercore") << "Canvas::render(); " << "targetFBO: " << fboName;

    // Check if the renderer must be replaced
    if (m_newRenderer) {
        // Deinitialize old renderer
        if (m_renderer && m_renderer->openGLContext()) {
            m_renderer->deinitContext(m_openGLContext);
        }

        // Replace renderer
        m_renderer = std::move(m_newRenderer);
    }

    // Check for a valid renderer
    if (!m_renderer || !m_viewport.isValid()) {
        return;
    }

    // Check if renderer needs to be initialized in context
    if (m_renderer->openGLContext() != m_openGLContext) {
        // Initialize renderer
        m_renderer->initContext(m_openGLContext);

        // Promote viewport information
        m_renderer->setViewport(m_viewport.value());
    }

    // Render
    m_renderer->render();
}

void Canvas::checkRedraw()
{
    if (!m_renderer) {
        return;
    }

    bool redraw = false;

    if (redraw) {
        this->redraw();
    }
}


} // namespace rendercore
