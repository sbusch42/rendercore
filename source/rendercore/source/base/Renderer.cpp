
#include <chrono>

#include <rendercore/base/Renderer.h>

#include <cppassist/logging/logging.h>

#include <glbinding/gl/gl.h>


namespace
{
    enum Query
    {
        PairOneStart = 0,
        PairOneEnd = 1,
        PairTwoStart = 2,
        PairTwoEnd = 3
    };
}


namespace rendercore
{


Renderer::Renderer(Environment * environment)
: m_environment(environment)
, m_viewport(0, 0, 0, 0)
, m_timeDelta(0.0f)
, m_timeMeasurement(false)
, m_useQueryPairOne(true)
, m_lastCPUDuration(0)
, m_currentCPUDuration(0)
, m_lastGPUDuration(0)
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

void Renderer::initContext(AbstractGLContext * context)
{
    cppassist::debug(2, "rendercore") << "Renderer::initContext()";

    // Create time queries
    gl::glGenQueries(4, m_queries.data());

    // Dummy querys for first frame
    if (m_useQueryPairOne)
    {
        gl::glQueryCounter(m_queries[Query::PairOneStart], gl::GL_TIMESTAMP);
        gl::glQueryCounter(m_queries[Query::PairOneEnd], gl::GL_TIMESTAMP);
    }
    else
    {
        gl::glQueryCounter(m_queries[Query::PairTwoStart], gl::GL_TIMESTAMP);
        gl::glQueryCounter(m_queries[Query::PairTwoEnd], gl::GL_TIMESTAMP);
    }

    onContextInit(context);
}

void Renderer::deinitContext(AbstractGLContext * context)
{
    cppassist::debug(2, "rendercore") << "Renderer::deinitContext()";
    onContextDeinit(context);
}

void Renderer::render()
{
    cppassist::debug(1, "rendercore") << "Renderer::render()";

    if (m_timeMeasurement)
    {
        // Get currently used queries
        auto usedStartQuery   = m_useQueryPairOne ? Query::PairOneStart : Query::PairTwoStart;
        auto usedEndQuery     = m_useQueryPairOne ? Query::PairOneEnd   : Query::PairTwoEnd;
        auto unusedStartQuery = m_useQueryPairOne ? Query::PairTwoStart : Query::PairOneStart;
        auto unusedEndQuery   = m_useQueryPairOne ? Query::PairTwoEnd   : Query::PairOneEnd;

        // Start CPU time measurement
        auto cpu_start = std::chrono::high_resolution_clock::now();

        // Start GPU time measurement
        gl::glQueryCounter(m_queries[unusedStartQuery], gl::GL_TIMESTAMP);

        // Execute rendering
        onRender();

        // Stop CPU time measurement
        auto cpu_end = std::chrono::high_resolution_clock::now();
        m_lastCPUDuration = m_currentCPUDuration;
        m_currentCPUDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(cpu_end - cpu_start).count();

        // Stop GPU time measurement
        gl::glQueryCounter(m_queries[unusedEndQuery], gl::GL_TIMESTAMP);

        // Get GPU values from last frame
        gl::GLuint64 gpu_start, gpu_end;
        gl::glGetQueryObjectui64v(m_queries[usedStartQuery], gl::GL_QUERY_RESULT, &gpu_start);
        gl::glGetQueryObjectui64v(m_queries[usedEndQuery], gl::GL_QUERY_RESULT, &gpu_end);
        m_lastGPUDuration = gpu_end - gpu_start;

        // Switch queries for next frame
        m_useQueryPairOne = !m_useQueryPairOne;
    }
    else
    {
        onRender();
    }
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

void Renderer::onContextInit(AbstractGLContext *)
{
}

void Renderer::onContextDeinit(AbstractGLContext *)
{
}

void Renderer::onRender()
{
}


} // namespace rendercore
