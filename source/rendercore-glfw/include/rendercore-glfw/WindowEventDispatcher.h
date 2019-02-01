
#pragma once

#include <memory>

#include <glm/fwd.hpp>

#include <rendercore-glfw/rendercore-glfw_api.h>


struct GLFWwindow;


namespace rendercore
{
namespace glfw
{


class Window;
class WindowEvent;


/**
*  @brief
*    Event dispatcher
*
*    Static class that handles the dispatching of GLWF events to windows.
*/
class RENDERCORE_GLFW_API WindowEventDispatcher
{
public:
    /**
    *  @brief
    *    Register window for event dispatching
    *
    *  @param[in] window
    *    Window (must NOT be null!)
    */
    static void registerWindow(Window * window);

    /**
    *  @brief
    *    Unregister window from event dispatching
    *
    *  @param[in] window
    *    Window (must NOT be null!)
    */
    static void deregisterWindow(Window * window);

protected:
    /**
    *  @brief
    *    Dispatch event to window
    *
    *  @param[in] window
    *    GLFW window (can be null)
    *  @param[in] event
    *    Event (can be null)
    *
    *  @remarks
    *    The event object will be destroyed after dispatching.
    */
    static void dispatchEvent(GLFWwindow * glfwWindow, std::unique_ptr<WindowEvent> && event);

    /**
    *  @brief
    *    Dispatch event to window
    *
    *  @param[in] window
    *    Window (can be null)
    *  @param[in] event
    *    Event (can be null)
    *
    *  @remarks
    *    The event object will be destroyed after dispatching.
    */
    static void dispatchEvent(Window * window, std::unique_ptr<WindowEvent> && event);

    /**
    *  @brief
    *    Find window object from GLFW window
    *
    *  @param[in] window
    *    GLFW window (can be null)
    *
    *  @return
    *    Window (can be null)
    */
    static Window * fromGLFW(GLFWwindow * glfwWindow);

    /**
    *  @brief
    *    Get current mouse position inside the given window
    *
    *  @param[in] window
    *    GLFW window (can be null)
    *
    *  @return
    *    Position, (0, 0) if mouse is not inside the window or window is invalid
    */
    static glm::ivec2 mousePosition(GLFWwindow * glfwWindow);

    // Event callbacks
    static void handleRefresh(GLFWwindow * glfwWindow);
    static void handleKey(GLFWwindow * glfwWindow, int key, int scanCode, int action, int modifiers);
    static void handleChar(GLFWwindow * glfwWindow, unsigned int character);
    static void handleMouse(GLFWwindow * glfwWindow, int button, int action, int modifiers);
    static void handleCursorPos(GLFWwindow * glfwWindow, double xPos, double yPos);
    static void handleCursorEnter(GLFWwindow * glfwWindow, int entered);
    static void handleScroll(GLFWwindow * glfwWindow, double xOffset, double yOffset);
    static void handleResize(GLFWwindow * glfwWindow, int width, int height);
    static void handleFramebufferResize(GLFWwindow * glfwWindow, int width, int height);
    static void handleMove(GLFWwindow * glfwWindow, int x, int y);
    static void handleFocus(GLFWwindow * glfwWindow, int focused);
    static void handleIconify(GLFWwindow * glfwWindow, int iconified);
    static void handleClose(GLFWwindow * glfwWindow);
};


} // namespace glfw
} // namespace rendercore
