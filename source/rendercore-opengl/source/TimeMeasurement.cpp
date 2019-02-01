
#include <rendercore-opengl/TimeMeasurement.h>

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
namespace opengl
{


TimeMeasurement::TimeMeasurement()
: m_useQueryPairOne(false)
, m_lastCPUDuration(0)
, m_currentCPUDuration(0)
, m_lastGPUDuration(0)
{
    // Create time queries
    gl::glGenQueries(4, m_queries.data());

    // Dummy querys for first frame
    if (m_useQueryPairOne) {
        gl::glQueryCounter(m_queries[Query::PairOneStart], gl::GL_TIMESTAMP);
        gl::glQueryCounter(m_queries[Query::PairOneEnd],   gl::GL_TIMESTAMP);
    } else {
        gl::glQueryCounter(m_queries[Query::PairTwoStart], gl::GL_TIMESTAMP);
        gl::glQueryCounter(m_queries[Query::PairTwoEnd],   gl::GL_TIMESTAMP);
    }
}

TimeMeasurement::~TimeMeasurement()
{
}

void TimeMeasurement::start()
{
    // Start CPU time measurement
    m_cpuTime = std::chrono::high_resolution_clock::now();

    // Start GPU time measurement
    gl::glQueryCounter(m_queries[m_useQueryPairOne ? Query::PairTwoStart : Query::PairOneStart], gl::GL_TIMESTAMP);
}

void TimeMeasurement::stop()
{
    // Get currently used queries
    auto usedStartQuery   = m_useQueryPairOne ? Query::PairOneStart : Query::PairTwoStart;
    auto usedEndQuery     = m_useQueryPairOne ? Query::PairOneEnd   : Query::PairTwoEnd;
    auto unusedEndQuery   = m_useQueryPairOne ? Query::PairTwoEnd   : Query::PairOneEnd;

    // Shift CPU measurement of last frame
    m_lastCPUDuration = m_currentCPUDuration;

    // Stop CPU time measurement
    auto cpuTime = std::chrono::high_resolution_clock::now();
    m_currentCPUDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(cpuTime - m_cpuTime).count();

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

uint64_t TimeMeasurement::currentCPUDuration() const
{
    return m_currentCPUDuration;
}

uint64_t TimeMeasurement::lastCPUDuration() const
{
    return m_lastCPUDuration;
}

uint64_t TimeMeasurement::lastGPUDuration() const
{
    return m_lastGPUDuration;
}


} // namespace opengl
} // namespace rendercore
