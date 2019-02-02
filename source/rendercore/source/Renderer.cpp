
#include <chrono>

#include <rendercore/Renderer.h>

#include <cppassist/logging/logging.h>


namespace rendercore
{


Renderer::Renderer()
: m_context(nullptr)
, m_viewport(0, 0, 0, 0)
, m_timeDelta(0.0f)
, m_needsUpdate(false)
, m_needsRedraw(false)
{
}

Renderer::~Renderer()
{
}

const AbstractContext * Renderer::context() const
{
    return m_context;
}

AbstractContext * Renderer::context()
{
    return m_context;
}

void Renderer::initContext(AbstractContext * context)
{
    cppassist::debug(0, "rendercore") << "Renderer::initContext()";

    // Check if renderer is already attached to this context
    if (m_context == context) {
        cppassist::error("rendercore") << "Renderer::initContext(): Renderer is already attached to this context.";
        return;
    }

    // Check if renderer is attached to another context
    if (m_context != nullptr) {
        cppassist::error("rendercore") << "Renderer::initContext(): Renderer is already attached to another context.";
        return;
    }

    // Initialize new context
    if (context) {
        // Save context
        m_context = context;

        // Initialize renderer in context
        onContextInit(context);
    }
}

void Renderer::deinitContext(AbstractContext * context)
{
    cppassist::debug(0, "rendercore") << "Renderer::deinitContext()";

    // Check if renderer is attached to the context
    if (m_context != context) {
        cppassist::error("rendercore") << "Renderer::deinitContext(): Renderer is not attached to this context.";
        return;
    }

    // Deinitialize context
    if (m_context) {
        // Deinitialize renderer in context
        onContextDeinit(context);

        // Reset context
        m_context = nullptr;
    }
}

glm::vec4 Renderer::viewport() const
{
    return m_viewport;
}

void Renderer::setViewport(const glm::vec4 & viewport)
{
    m_viewport = viewport;
}

float Renderer::timeDelta() const
{
    return m_timeDelta;
}

void Renderer::setTimeDelta(float timeDelta)
{
    m_timeDelta = timeDelta;
}

bool Renderer::needsUpdate() const
{
    return m_needsUpdate;
}

void Renderer::scheduleUpdate()
{
    m_needsUpdate = true;
}

void Renderer::update()
{
    cppassist::debug(1, "rendercore") << "Renderer::update()";

    // Reset flag
    m_needsUpdate = false;

    // Update
    onUpdate();
}

bool Renderer::needsRedraw() const
{
    return m_needsRedraw;
}

void Renderer::scheduleRedraw()
{
    m_needsRedraw = true;
}

void Renderer::render()
{
    cppassist::debug(1, "rendercore") << "Renderer::render()";

    // Reset flag
    m_needsRedraw = false;

    // Render frame
    onRender();
}

void Renderer::onContextInit(AbstractContext *)
{
}

void Renderer::onContextDeinit(AbstractContext *)
{
}

void Renderer::onUpdate()
{
}

void Renderer::onRender()
{
}


} // namespace rendercore
