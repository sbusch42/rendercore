
// [TODO] Review
#include <rendercore-glfw/GLContext.h>

#include <cassert>

#ifdef WIN32
    #include <windows.h>
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> // specifies APIENTRY, should be after Error.h include,
                        // which requires APIENTRY in windows..

#include <rendercore/base/GLContextUtils.h>
#include <rendercore/base/GLContextFormat.h>


using namespace rendercore;


namespace rendercore_glfw
{


void GLContext::updateSwapBehavior(rendercore::GLContextFormat::SwapBehavior swapBehavior)
{
    switch (swapBehavior)
    {
    case rendercore::GLContextFormat::SwapBehavior::DoubleBuffering:
        glfwSwapInterval(1);
        break;

    default:
        glfwSwapInterval(0);
    }
}

GLContext::GLContext(GLFWwindow * window)
: m_window(window)
{
    assert(window);

    // Activate context
    use();

    // Initialize glbinding and globjects in context (needed for context utils)
    initializeBindings([](const char * name) -> glbinding::ProcAddress
    {
        return glfwGetProcAddress(name);
    });

    // Read context format
    m_format = GLContextUtils::retrieveFormat();

    // Deactivate context
    release();
}

GLContext::~GLContext()
{
}

GLFWwindow * GLContext::window() const
{
    return m_window;
}

void GLContext::use() const
{
    if (m_window)
    {
        glfwMakeContextCurrent(m_window);
    }
}

void GLContext::release() const
{
    if (m_window && m_window == glfwGetCurrentContext())
    {
        glfwMakeContextCurrent(nullptr);
    }
}


} // namespace rendercore_glfw
