
#include <chrono>

#include <rendercore/Renderer.h>

#include <cppassist/logging/logging.h>


namespace rendercore
{


Renderer::Renderer(Environment * environment)
: m_environment(environment)
, m_context(nullptr)
, m_viewport(0, 0, 0, 0)
, m_timeDelta(0.0f)
{
}

Renderer::~Renderer()
{
}

const Environment * Renderer::environment() const
{
    return m_environment;
}

Environment * Renderer::environment()
{
    return m_environment;
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

void Renderer::render()
{
    cppassist::debug(1, "rendercore") << "Renderer::render()";

    // Render frame
    onRender();
}

bool Renderer::needsRedraw() const
{
    return false;
}

void Renderer::setViewport(const glm::vec4 & viewport)
{
    m_viewport = viewport;
}

void Renderer::setTimeDelta(float timeDelta)
{
    m_timeDelta = timeDelta;
}

void Renderer::onContextInit(AbstractContext *)
{
}

void Renderer::onContextDeinit(AbstractContext *)
{
}

void Renderer::onRender()
{
}


} // namespace rendercore
