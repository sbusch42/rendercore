
#pragma once


#include <memory>
#include <queue>
#include <set>
#include <string>

#include <glm/vec2.hpp>

#include <rendercore-opengl/GLContextFormat.h>

#include <rendercore-glfw/rendercore-glfw_api.h>


struct GLFWwindow;
struct GLFWmonitor;


namespace rendercore
{


namespace opengl
{


class AbstractGLContext;


}


namespace glfw
{


class GLContext;
class WindowEvent;
class KeyEvent;
class MouseEvent;
class MouseEnterEvent;
class MouseLeaveEvent;
class MoveEvent;
class ResizeEvent;
class PaintEvent;
class CloseEvent;
class FocusEvent;
class IconifyEvent;


/**
*  @brief
*    Window with OpenGL context
*/
class RENDERCORE_GLFW_API Window
{
    friend class Application;
    friend class WindowEventDispatcher;

public:
    /**
    *  @brief
    *    Get list of windows
    *
    *  @return
    *    List of open windows
    */
    static const std::set<Window*> & instances();

private:
    static std::set<Window*> s_instances; ///< List of window instances

public:
    /**
    *  @brief
    *    Constructor
    */
    Window();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Window();

    /**
    *  @brief
    *    Set OpenGL context format
    *
    *  @param[in] format
    *    The desired OpenGL context format
    *
    *  @return
    *    'true' if the format could be set, else 'false'
    *
    *  @remarks
    *    The context format can only be set before the window
    *    has been created. Afterwards, the function will fail
    *    and the context format will not be changed.
    */
    bool setContextFormat(const rendercore::opengl::GLContextFormat & format);

    /**
    *  @brief
    *    Create window
    *
    *  @return
    *    'true' if window could be created, else 'false'
    *
    *  @remarks
    *    If the window has already been created, this function will fail.
    */
    bool create();

    /**
    *  @brief
    *    Destroy window
    */
    void destroy();

    /**
    *  @brief
    *    Get OpenGL context
    *
    *  @return
    *    OpenGL context (can be null)
    */
    const GLContext * context() const;

    /**
    *  @brief
    *    Get OpenGL context
    *
    *  @return
    *    OpenGL context (can be null)
    */
    GLContext * context();

    /**
    *  @brief
    *    Show window (make it visible)
    */
    void show();

    /**
    *  @brief
    *    Hide window (make it invisible)
    */
    void hide();

    /**
    *  @brief
    *    Close window
    */
    void close();

    /**
    *  @brief
    *    Check if window is in fullscreen-mode
    *
    *  @return
    *    'true' if window is in fullscreen-mode, else 'false'
    */
    bool isFullscreen() const;

    /**
    *  @brief
    *    Set fullscreen-mode
    *
    *  @param[in] fullscreen
    *    'true' to switch to fullscreen-mode, 'false' to switch to windowed-mode
    */
    void setFullscreen(bool fullscreen);

    /**
    *  @brief
    *    Get window position
    *
    *  @return
    *    Window position (in pixels)
    */
    glm::ivec2 position() const;

    /**
    *  @brief
    *    Get window size
    *
    *  @return
    *    Window size (in pixels)
    */
    glm::ivec2 size() const;

    /**
    *  @brief
    *    Set window size
    *
    *  @param[in] width
    *    Window width (in pixels)
    *  @param[in] height
    *    Window height (in pixels)
    */
    void setSize(int width, int height);

    /**
    *  @brief
    *    Get framebuffer size
    *
    *  @return
    *    Framebuffer size (in device pixels, may be larger than virtual window resolution)
    */
    glm::ivec2 framebufferSize() const;

    /**
    *  @brief
    *    Get window title
    *
    *  @return
    *    Window title
    */
    const std::string & title() const;

    /**
    *  @brief
    *    Set window title
    *
    *  @param[in] title
    *    Window title
    */
    void setTitle(const std::string & title);

    /**
    *  @brief
    *    Query input mode
    *
    *  @param[in] mode
    *    Input mode
    *
    *  @return
    *    Value of input mode
    *
    *  @remarks
    *    Possible values include GLFW_CURSOR, GLFW_STICKY_KEYS,
    *    or GLFW_STICKY_MOUSE_BUTTONS. For more information,
    *    refer to GLFW docs to glfwGetInputMode.
    */
    int inputMode(int mode) const;

    /**
    *  @brief
    *    Set input mode
    *
    *  @param[in] mode
    *    Input mode
    *  @param[in] value
    *    Input mode value
    *
    *  @remarks
    *    Possible values include GLFW_CURSOR, GLFW_STICKY_KEYS,
    *    or GLFW_STICKY_MOUSE_BUTTONS. For more information,
    *    refer to GLFW docs to glfwGetInputMode.
    */
    void setInputMode(int mode, int value);

    /**
    *  @brief
    *    Check if application quits when windows gets closed
    *
    *  @return
    *    'true' if window quits the application when closed, else 'false'
    */
    bool quitsOnDestroy() const;

    /**
    *  @brief
    *    Set if application quits when the window gets closed
    *
    *  @param[in] quitOnDestroy
    *    'true' if window quits the application when closed, else 'false'
    *
    *  @remarks
    *    If enabled, this causes an application wide quit message to be posted
    *    when the window gets destroyed. Hence, the MainLoop will be quit
    *    and all other remaining windows destroyed.
    */
    void setQuitOnDestroy(bool quitOnDestroy);

    /**
    *  @brief
    *    Schedule an update on the window
    *
    *  @remarks
    *    When calling this function, an empty event will be sent to the
    *    message queue, causing the idle-function of the window to be
    *    called during the next event processing.
    */
    void update();

    /**
    *  @brief
    *    Schedule a repaint on the window
    *
    *  @remarks
    *    When calling this function, a redraw-event will be sent to the
    *    message queue, causing the window to be repainted within the
    *    next event processing.
    */
    void repaint();

    /**
    *  @brief
    *    Swap front and back buffer
    */
    void swap();

    /**
    *  @brief
    *    Called once every mainloop iteration
    */
    void idle();

protected:
    /**
    *  @brief
    *    Get GLFW window handle
    *
    *  @return
    *    GLFW window (can be null)
    */
    GLFWwindow * internalWindow() const;

    /**
    *  @brief
    *    Add event to the window's event queue
    *
    *  @param[in] event
    *    Event (can be null)
    */
    void queueEvent(std::unique_ptr<WindowEvent> && event);

    /**
    *  @brief
    *    Check if window has events waiting
    *
    *  @return
    *    'true' if events are waiting in the window's event queue, else 'false'
    */
    bool hasPendingEvents();

    /**
    *  @brief
    *    Process all waiting events and dispatch them to event handling
    */
    void processEvents();

    /**
    *  @brief
    *    Check for idle event
    *
    *  @remarks
    *    If update() has been called on the window, an update event
    *    will be added to the window's event queue. This needs to be
    *    done as a separate call to avoid event processing to get stuck
    *    in an endless loop. Make sure to call Application::pollEvents(),
    *    checkUpdateEvent() and checkRepaintEvent() in turn.
    */
    void checkUpdateEvent();

    /**
    *  @brief
    *    Check for repaint event
    *
    *  @remarks
    *    If repaint() has been called on the window, a repaint event
    *    will be added to the window's event queue. This needs to be
    *    done as a separate call to avoid event processing to get stuck
    *    in an endless loop. Make sure to call Application::pollEvents(),
    *    checkUpdateEvent() and checkRepaintEvent() in turn.
    */
    void checkRepaintEvent();

    /**
    *  @brief
    *    Handle window event
    *
    *  @param[in] event
    *    Window event
    */
    void handleEvent(WindowEvent & event);

    /**
    *  @brief
    *    Remove all waiting events from the queue
    */
    void clearEventQueue();

    /**
    *  @brief
    *    Create internal window and OpenGL context
    *
    *  @param[in] format
    *    The desired OpenGL context format
    *  @param[in] width
    *    Window width (in pixels)
    *  @param[in] height
    *    Window height (in pixels)
    *  @param[in] monitor
    *    GLWF monitor handle (can be null)
    *
    *  @return
    *    'true' if context could be created, else 'false'
    *
    *  @remarks
    *    This function will actually create a new window with the given context
    *    format, so any previously obtained window IDs will be rendered invalid.
    */
    bool createInternalWindow(const rendercore::opengl::GLContextFormat & format, int width, int height, GLFWmonitor * monitor = nullptr);

    /**
    *  @brief
    *    Destroy internal window and OpenGL context
    *
    *  @remarks
    *    This function will actually destroy the current window.
    */
    void destroyInternalWindow();

    // Event handlers, to be overwritten in derived classes
    virtual void onContextInit();
    virtual void onContextDeinit();
    virtual void onResize(ResizeEvent & event);
    virtual void onFramebufferResize(ResizeEvent & event);
    virtual void onMove(MoveEvent & event);
    virtual void onPaint(PaintEvent & event);
    virtual void onKeyPress(KeyEvent & event);
    virtual void onKeyRelease(KeyEvent & event);
    virtual void onMousePress(MouseEvent & event);
    virtual void onMouseMove(MouseEvent & event);
    virtual void onMouseRelease(MouseEvent & event);
    virtual void onMouseEnter(MouseEnterEvent & event);
    virtual void onMouseLeave(MouseLeaveEvent & event);
    virtual void onScroll(MouseEvent & event);
    virtual void onFocus(FocusEvent & event);
    virtual void onIconify(IconifyEvent & event);
    virtual void onClose(CloseEvent & event);
    virtual void onIdle();

protected:
    std::string                              m_title;            ///< Window title
    rendercore::opengl::GLContextFormat      m_format;           ///< The desired OpenGL context format
    GLFWwindow                             * m_window;           ///< GLFW window (can be null)
    std::queue<std::unique_ptr<WindowEvent>> m_eventQueue;       ///< List of events to be processed by the window
    bool                                     m_fullscreen;       ///< 'true' if window is in fullscreen mode, else 'false'
    glm::ivec2                               m_windowedModeSize; ///< Size of window when returned from fullscreen mode
    bool                                     m_quitOnDestroy;    ///< Quit application when window is closed?
    bool                                     m_needsUpdate;      ///< Has an update be scheduled?
    bool                                     m_needsRepaint;     ///< Has a repaint be scheduled?
    std::unique_ptr<GLContext>               m_context;          ///< OpenGL context (can be null)
};


} // namespace glfw
} // namespace rendercore
