
#include <chrono>

#include <rendercore/Renderer.h>

#include <cppassist/logging/logging.h>


namespace rendercore
{


Renderer::Renderer(GpuContainer * container)
: GpuContainer(container)
, m_viewport(0, 0, 0, 0)
, m_timeDelta(0.0f)
, m_needsUpdate(false)
, m_needsRedraw(false)
{
}

Renderer::~Renderer()
{
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

void Renderer::onUpdate()
{
}

void Renderer::onRender()
{
}


} // namespace rendercore
