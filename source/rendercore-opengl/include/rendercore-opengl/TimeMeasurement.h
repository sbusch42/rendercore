
#pragma once


#include <array>
#include <chrono>

#include <glm/vec4.hpp>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Class to measure the performance on GPU and CPU
*/
class RENDERCORE_OPENGL_API TimeMeasurement
{
public:
    //@{
    /**
    *  @brief
    *    Constructor
    */
    TimeMeasurement();

    /**
    *  @brief
    *    Destructor
    */
    ~TimeMeasurement();

    /**
    *  @brief
    *    Start measuring the time
    */
    void start();

    /**
    *  @brief
    *    Stop measuring the time
    */
    void stop();

    /**
    *  @brief
    *    Get time measured on the CPU for the current frame
    *
    *  @return
    *    Time (in nanoseconds)
    */
    uint64_t currentCPUDuration() const;

    /**
    *  @brief
    *    Get time measured on the CPU for the last frame (one frame behind)
    *
    *  @return
    *    Time (in nanoseconds)
    */
    uint64_t lastCPUDuration() const;

    /**
    *  @brief
    *    Get time measured on the GPU for the last frame (one frame behind)
    *
    *  @return
    *    Time (in nanoseconds)
    */
    uint64_t lastGPUDuration() const;

protected:
    bool     m_useQueryPairOne;    ///< Flag indicating which queries are currently used
    uint64_t m_lastCPUDuration;    ///< Time spent in onRender last frame (in nanoseconds)
    uint64_t m_currentCPUDuration; ///< Time spent in onRender current frame (in nanoseconds)
    uint64_t m_lastGPUDuration;    ///< Time for GPU commands issued during onRender (in nanoseconds)

    std::chrono::time_point<std::chrono::high_resolution_clock> m_cpuTime; ///< Last CPU time stamp
    std::array<unsigned int, 4>                                 m_queries; ///< OpenGL query objects (front/back; start/end)
};


} // namespace opengl
} // namespace rendercore
