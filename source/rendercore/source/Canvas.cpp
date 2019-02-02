
#include <rendercore/Canvas.h>

#include <cppassist/logging/logging.h>

#include <rendercore/Renderer.h>


namespace rendercore
{


Canvas::Canvas()
: m_context(nullptr)
, m_timeDelta(0.0f)
{
}

Canvas::~Canvas()
{
}

const AbstractContext * Canvas::context() const
{
    return m_context;
}

AbstractContext * Canvas::context()
{
    return m_context;
}

void Canvas::initContext(AbstractContext * context)
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);
    cppassist::debug(0, "rendercore") << "Canvas::initContext()";

    // Check if canvas is already attached to this context
    if (m_context == context) {
        cppassist::error("rendercore") << "Canvas::initContext(): Canvas is already attached to this context.";
        return;
    }

    // Check if canvas is attached to another context
    if (m_context != nullptr) {
        cppassist::error("rendercore") << "Canvas::initContext(): Canvas is already attached to another context.";
        return;
    }

    // Initialize context
    if (context) {
        // Save context
        m_context = context;

        // The renderer will be initialized in the new context on the next rendering call
        wakeup();
    }
}

void Canvas::deinitContext(AbstractContext * context)
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);
    cppassist::debug(0, "rendercore") << "Canvas::deinitContext()";

    // Check if canvas is attached to the context
    if (m_context != context) {
        cppassist::error("rendercore") << "Canvas::deinitContext(): Canvas is not attached to this context.";
        return;
    }

    // Deinitialize context
    if (m_context) {
        // Deinitialize renderer in context
        if (m_renderer) {
            m_renderer->deinitContext(m_context);
        }

        // Reset context
        m_context = nullptr;
    }

    // Reset viewport
    m_viewport.invalidate();
}

void Canvas::setRenderer(std::unique_ptr<Renderer> && renderer)
{
    // Set new renderer to replace the old one
    m_newRenderer = std::move(renderer);
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
}

float Canvas::timeDelta() const
{
    return m_timeDelta;
}

void Canvas::updateTime()
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);

    // In multithreaded viewers, updateTime() might get called several times
    // before update(). Therefore, the time delta is accumulated until the
    // renderer is actually updated, and then reset in the method update().

    // Get number of milliseconds since last call
    auto duration = m_clock.elapsed();
    m_clock.reset();

    // Determine and update time delta
    float timeDelta = std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
    m_timeDelta += timeDelta;
}

bool Canvas::needsUpdate() const
{
    // Check on renderer
    return m_renderer ? m_renderer->needsUpdate() : false;
}

void Canvas::scheduleUpdate()
{
    // Schedule update on renderer
    if (m_renderer) {
        m_renderer->scheduleUpdate();
    }
}

void Canvas::update()
{
    // [DEBUG]
    cppassist::debug(0, "rendercore") << "Canvas::update()";

    // Check for a valid renderer
    if (!m_renderer) {
        return;
    }

    // Update timing
    m_renderer->setTimeDelta(m_timeDelta);

    // Update renderer
    m_renderer->update();

    // Reset time delta
    m_timeDelta = 0.0f;
}

bool Canvas::needsRedraw() const
{
    // Check on renderer
    return m_renderer ? m_renderer->needsRedraw() : false;
}

void Canvas::scheduleRedraw()
{
    // Schedule redraw on renderer
    if (m_renderer) {
        m_renderer->scheduleUpdate();
    }
}

void Canvas::render()
{
    std::lock_guard<std::recursive_mutex> lock(this->m_mutex);

    // [DEBUG]
    cppassist::debug(0, "rendercore") << "Canvas::render()";

    // Check if the renderer must be replaced
    if (m_newRenderer) {
        // Deinitialize old renderer
        if (m_renderer && m_renderer->context()) {
            m_renderer->deinitContext(m_context);
        }

        // Replace renderer
        m_renderer = std::move(m_newRenderer);
    }

    // Check for a valid renderer
    if (!m_renderer || !m_viewport.isValid()) {
        return;
    }

    // Check if renderer needs to be initialized in context
    if (m_renderer->context() != m_context) {
        // Initialize renderer
        m_renderer->initContext(m_context);

        // Promote viewport information
        m_renderer->setViewport(m_viewport.value());
    }

    // Render
    m_renderer->render();
}


} // namespace rendercore
