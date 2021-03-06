
#pragma once


#include <glm/vec2.hpp>

#include <rendercore-glfw/rendercore-glfw_api.h>


namespace rendercore
{
namespace glfw
{


class Window;


/**
*  @brief
*    Base class for window events
*/
class RENDERCORE_GLFW_API WindowEvent
{
public:
    /**
    *  @brief
    *    Enumeration of all supported event types
    */
    enum class Type
    {
        KeyPress
      , KeyRelease
      , KeyTyped
      , MousePress
      , MouseRelease
      , MouseMove
      , MouseEnter
      , MouseLeave
      , Scroll
      , Resize
      , FrameBufferResize
      , Move
      , Close
      , Focus
      , Iconify
      , Paint
    };

public:
    /**
    *  @brief
    *    Destructor
    */
    virtual ~WindowEvent();

    /**
    *  @brief
    *    Get event type
    *
    *  @return
    *    Event type
    */
    Type type() const;

    /**
    *  @brief
    *    Get accepted state
    *
    *  @return
    *    'true' if accepted, else 'false'
    */
    bool isAccepted() const;

    /**
    *  @brief
    *    Get ignored state
    *
    *  @return
    *    'true' if ignored, else 'false'
    *
    *  @remarks
    *    An event is ignored if it is not accepted
    */
    bool isIgnored() const;

    /**
    *  @brief
    *    Set accepted state
    *
    *  @param[in] accepted
    *    'true' if accepted, else 'false'
    */
    void setAccepted(bool accepted);

    /**
    *  @brief
    *    Set accepted state to 'true'
    */
    void accept();

    /**
    *  @brief
    *    Set ignored state to 'true'
    *
    *  @remarks
    *    This is identical to setting the accepted state to 'false'
    */
    void ignore();

    /**
    *  @brief
    *    Get associated window
    *
    *  @return
    *    Window (can be null)
    */
    const Window * window() const;

    /**
    *  @brief
    *    Get associated window
    *
    *  @return
    *    Window (can be null)
    */
    Window * window();

    /**
    *  @brief
    *    Set associated window
    *
    *  @param[in] window
    *    Window (can be null)
    */
    void setWindow(Window * window);

protected:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] type
    *    The event type
    *
    *  @remarks
    *    Initializes an event of given type that is not accepted
    *    and has no associated window.
    */
    WindowEvent(Type type);

protected:
    Type     m_type;     ///< The event type
    bool     m_accepted; ///< The accepted state to prevent further bubbling
    Window * m_window;   ///< The associated window, may be null
};


/**
*  @brief
*    Representation of a keyboard event
*/
class RENDERCORE_GLFW_API KeyEvent : public WindowEvent
{
public:
    KeyEvent(int key, int scanCode, int action, int modifiers);
    explicit KeyEvent(unsigned int character);

    int key() const;
    int scanCode() const;
    int action() const;
    int modifiers() const;
    unsigned int character() const;

protected:
    int m_key;
    int m_scanCode;
    int m_action;
    int m_modifiers;
    unsigned int m_character;
};


/**
*  @brief
*    Representation of a mouse event (including scroll events)
*/
class RENDERCORE_GLFW_API MouseEvent : public WindowEvent
{
public:
    MouseEvent(const glm::ivec2 & pos);
    MouseEvent(const glm::ivec2 & pos, int button, int action, int modifiers);
    MouseEvent(const glm::ivec2 & pos, const glm::vec2 & delta, int modifiers);

    int button() const;
    int action() const;
    int modifiers() const;

    const glm::ivec2 & pos() const;
    const glm::vec2 & delta() const;

    int x() const;
    int y() const;

protected:
    int m_button;
    int m_action;
    int m_modifiers;

    glm::ivec2 m_pos;
    glm::vec2  m_delta;
};


/**
*  @brief
*    Representation of a mouse event (cursor enters the window)
*/
class RENDERCORE_GLFW_API MouseEnterEvent : public WindowEvent
{
public:
    MouseEnterEvent();
};


/**
*  @brief
*    Representation of a mouse event (cursor leaves the window)
*/
class RENDERCORE_GLFW_API MouseLeaveEvent : public WindowEvent
{
public:
    MouseLeaveEvent();
};


/**
*  @brief
*    Representation of a window move event (window has been moved)
*/
class RENDERCORE_GLFW_API MoveEvent : public WindowEvent
{
public:
    MoveEvent(const glm::ivec2 & pos);

    const glm::ivec2 & pos() const;

    int x() const;
    int y() const;

protected:
    glm::ivec2 m_pos;
};


/**
*  @brief
*    Representation of a window resize event (window has been resized)
*/
class RENDERCORE_GLFW_API ResizeEvent : public WindowEvent
{
public:
    ResizeEvent(const glm::ivec2 & size, bool framebuffer = false);

    const glm::ivec2 & size() const;

    int width() const;
    int height() const;

protected:
    glm::ivec2 m_size;
};


/**
*  @brief
*    Representation of a paint event (window has to be redrawn)
*/
class RENDERCORE_GLFW_API PaintEvent : public WindowEvent
{
public:
    PaintEvent();
};


/**
*  @brief
*    Representation of a window close event (window has been closed)
*/
class RENDERCORE_GLFW_API CloseEvent : public WindowEvent
{
public:
    CloseEvent();
};


/**
*  @brief
*    Representation of a focus event (window has received or lost the keyboard focus)
*/
class RENDERCORE_GLFW_API FocusEvent : public WindowEvent
{
public:
    FocusEvent(bool hasFocus);
    bool hasFocus() const;

protected:
    bool m_hasFocus;
};


/**
*  @brief
*    Representation of a window iconify event (window has been minimized)
*/
class RENDERCORE_GLFW_API IconifyEvent : public WindowEvent
{
public:
    IconifyEvent(bool isIconified);
    bool isIconified() const;

protected:
    bool m_isIconified;
};


} // namespace glfw
} // namespace rendercore
