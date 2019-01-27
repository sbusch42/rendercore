
// [TODO] Review
#pragma once


#include <rendercore-opengl/AbstractGLContextFactory.h>

#include <rendercore-glfw/rendercore-glfw_api.h>


struct GLFWmonitor;


namespace rendercore
{
namespace glfw
{


/**
*  @brief
*    OpenGL context factory
*/
class RENDERCORE_GLFW_API GLContextFactory : public rendercore::opengl::AbstractGLContextFactory
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] monitor
    *    GLFW monitor (if valid, fullscreen mode is used, else windowed mode)
    *  @param[in] width
    *    Window width
    *  @param[in] height
    *    Window height
    */
    GLContextFactory(GLFWmonitor * monitor, unsigned int width, unsigned int height);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~GLContextFactory();

    // Virtual rendercore::AbstractGLContextFactory functions
    virtual std::unique_ptr<rendercore::opengl::AbstractGLContext> createContext(const rendercore::opengl::GLContextFormat & format) const override;

private:
    /**
    *  @brief
    *    Set GLFW states and hints to select the given OpenGL context format
    *
    *  @param[in] format
    *    OpenGL context format
    */
    static void initializeGLFWState(const rendercore::opengl::GLContextFormat & format);

private:
    GLFWmonitor * m_monitor; ///< GLFW monitor (if valid, fullscreen mode is used, else windowed mode)
    unsigned int  m_width;   ///< Window width
    unsigned int  m_height;  ///< Window height
};


} // namespace glfw
} // namespace rendercore
