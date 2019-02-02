
#include <rendercore-glfw/RenderWindow.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <cppassist/memory/make_unique.h>

#include <globjects/Framebuffer.h>

#include <rendercore/Canvas.h>

#include <rendercore-glfw/GLContext.h>
#include <rendercore-glfw/WindowEvent.h>


namespace rendercore
{
namespace glfw
{


RenderWindow::RenderWindow()
: m_canvas(cppassist::make_unique<Canvas>())
{
    // Connect to wakeup-signal
    m_canvas->wakeup.connect([this] ()
    {
        // Schedule update on the window
        update();
    } );
}

RenderWindow::~RenderWindow()
{
}

Canvas * RenderWindow::canvas() const
{
    return m_canvas.get();
}

void RenderWindow::onContextInit()
{
    m_canvas->initContext(m_context.get());
}

void RenderWindow::onContextDeinit()
{
    m_canvas->deinitContext(m_context.get());
}

void RenderWindow::onResize(ResizeEvent & event)
{
    m_virtualSize = event.size();
}

void RenderWindow::onFramebufferResize(ResizeEvent & event)
{
    m_deviceSize = event.size();

    m_canvas->setViewport(
        glm::vec4(0, 0, m_deviceSize.x,  m_deviceSize.y)
    );
}

void RenderWindow::onMove(MoveEvent &)
{
}

void RenderWindow::onPaint(PaintEvent &)
{
    // [TODO] Optimize memory reallocation problem
    auto defaultFBO = globjects::Framebuffer::defaultFBO();

    // Render on canvas
    m_canvas->render();
}

void RenderWindow::onKeyPress(KeyEvent & event)
{
    // Skip auto-repeated key events
    if (event.action() == GLFW_REPEAT) {
        return;
    }

    // Promote event to canvas
    // [TODO]
    /*
    m_canvas->promoteKeyPress(
        fromGLFWKeyCode(event.key()),
        fromGLFWModifier(event.modifiers())
    );
    */

    // ESC: Close window
    if (event.key() == GLFW_KEY_ESCAPE) {
        close();
    }

    // F11/ALT+ENTER: Toogle fullscreen
    if (event.key() == GLFW_KEY_F11 || (event.key() == GLFW_KEY_ENTER && (event.modifiers() & GLFW_MOD_ALT) != 0) ) {
        setFullscreen(!isFullscreen());
    }
}

void RenderWindow::onKeyRelease(KeyEvent &)
{
    // Promote event to canvas
    // [TODO]
    /*
    m_canvas->promoteKeyRelease(
        fromGLFWKeyCode(event.key()),
        fromGLFWModifier(event.modifiers())
    );
    */
}

void RenderWindow::onMousePress(MouseEvent &)
{
    // Promote event to canvas
    // [TODO]
    /*
    m_canvas->promoteMousePress(
        fromGLFWMouseButton(event.button())
      , event.pos()
      , event.modifiers()
    );
    */
}

void RenderWindow::onMouseRelease(MouseEvent &)
{
    // Promote event to canvas
    // [TODO]
    /*
    m_canvas->promoteMouseRelease(
        fromGLFWMouseButton(event.button())
      , event.pos()
      , event.modifiers()
    );
    */
}

void RenderWindow::onMouseMove(MouseEvent &)
{
    // Promote event to canvas
    // [TODO]
    /*
    m_canvas->promoteMouseMove(event.pos(), event.modifiers());
    */
}

void RenderWindow::onMouseEnter(MouseEnterEvent &)
{
    // Promote event to canvas
    // [TODO]
}

void RenderWindow::onMouseLeave(MouseLeaveEvent &)
{
    // Promote event to canvas
    // [TODO]
}

void RenderWindow::onScroll(MouseEvent &)
{
    // Promote event to canvas
    // [TODO]
    /*
    m_canvas->promoteMouseWheel(
        event.delta()
      , event.pos()
      , 0
    );
    */
}

void RenderWindow::onFocus(FocusEvent &)
{
}

void RenderWindow::onIconify(IconifyEvent &)
{
}

void RenderWindow::onIdle()
{
    // Update time delta
    m_canvas->updateTime();

    // Update simulation
    m_canvas->update();

    // Is another simulation update needed?
    if (m_canvas->needsUpdate()) {
        // Schedule update
        this->update();
    }

    // Is a repaint needed?
    if (m_canvas->needsRedraw()) {
        // Schedule repaint
        this->repaint();
    }
}

/*
MouseButton RenderWindow::fromGLFWMouseButton(int button) const
{
    switch (button)
    {
        case GLFW_MOUSE_BUTTON_1: return MouseButton1;
        case GLFW_MOUSE_BUTTON_2: return MouseButton2;
        case GLFW_MOUSE_BUTTON_3: return MouseButton3;
        case GLFW_MOUSE_BUTTON_4: return MouseButton4;
        case GLFW_MOUSE_BUTTON_5: return MouseButton5;
        case GLFW_MOUSE_BUTTON_6: return MouseButton6;
        case GLFW_MOUSE_BUTTON_7: return MouseButton7;
        case GLFW_MOUSE_BUTTON_8: return MouseButton8;
        default:                  return NoMouseButton;
    }
}

Key RenderWindow::fromGLFWKeyCode(int key) const
{
    // We are using the same key code table as GLFW
    return static_cast<Key>(key);
}

KeyModifier RenderWindow::fromGLFWModifier(int modifier) const
{
    //We are using the same modifier code table as GLFW
    return static_cast<KeyModifier>(modifier);
}
*/


} // namespace glfw
} // namespace rendercore
