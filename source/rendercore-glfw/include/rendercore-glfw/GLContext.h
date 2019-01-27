
// [TODO] Review
#pragma once


#include <rendercore/base/AbstractGLContext.h>

#include <rendercore-glfw/rendercore-glfw_api.h>


struct GLFWwindow;


namespace rendercore_glfw
{


/**
*  @brief
*    OpenGL context implementation based on GLFW
*/
class RENDERCORE_GLFW_API GLContext : public rendercore::AbstractGLContext
{
public:
    /**
    *  @brief
    *    Update swap behavior
    *
    *  @param[in] swapBehavior
    *    The new behavior for swapping the buffers
    *
    *  @remarks
    *    Operates on the current OpenGL context
    */
    static void updateSwapBehavior(rendercore::GLContextFormat::SwapBehavior swapBehavior);

public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] window
    *    GLFW window that contains the context
    */
    GLContext(GLFWwindow * window);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~GLContext();

    /**
    *  @brief
    *    Get GLFW window
    *
    *  @return
    *    GLFW window that contains the context (cannot be null)
    */
    GLFWwindow * window() const;

    // Virtual rendercore::AbstractContext functions
    virtual void use() const override;
    virtual void release() const override;

protected:
    GLFWwindow * m_window;  ///< GLFW window that contains the context (cannot be null)
};


} // namespace rendercore_glfw
