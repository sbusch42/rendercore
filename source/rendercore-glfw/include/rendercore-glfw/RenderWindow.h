
#pragma once


#include <memory>

#include <glm/vec2.hpp>

#include <rendercore-glfw/Window.h>


namespace rendercore
{


class Canvas;


namespace glfw
{


/**
*  @brief
*    Default rendering window
*/
class RENDERCORE_GLFW_API RenderWindow : public Window
{
public:
    /**
    *  @brief
    *    Constructor
    */
    RenderWindow();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~RenderWindow();

    /**
    *  @brief
    *    Get canvas
    *
    *  @return
    *    Canvas that is rendered on
    */
    rendercore::Canvas * canvas() const;

protected:
    // Virtual Window functions
    virtual void onContextInit() override;
    virtual void onContextDeinit() override;
    virtual void onResize(ResizeEvent & event) override;
    virtual void onFramebufferResize(ResizeEvent & event) override;
    virtual void onMove(MoveEvent & event) override;
    virtual void onPaint(PaintEvent & event) override;
    virtual void onKeyPress(KeyEvent & event) override;
    virtual void onKeyRelease(KeyEvent & event) override;
    virtual void onMousePress(MouseEvent & event) override;
    virtual void onMouseRelease(MouseEvent & event) override;
    virtual void onMouseMove(MouseEvent & event) override;
    virtual void onMouseEnter(MouseEnterEvent & event) override;
    virtual void onMouseLeave(MouseLeaveEvent & event) override;
    virtual void onScroll(MouseEvent & event) override;
    virtual void onFocus(FocusEvent & event) override;
    virtual void onIconify(IconifyEvent & event) override;
    virtual void onIdle() override;

    /**
    *  @brief
    *    Convert GLFW mouse button into rendercore mouse button
    *
    *  @param[in] button
    *    GLFW mouse button
    *
    *  @return
    *    rendercore mouse button
    */
    // rendercore::MouseButton fromGLFWMouseButton(int button) const;

    /**
    *  @brief
    *    Convert GLFW key code into rendercore key code
    *
    *  @param[in] key
    *    GLFW key code
    *
    *  @return
    *    rendercore key code
    */
    // rendercore::Key fromGLFWKeyCode(int key) const;

    /**
    *  @brief
    *    Convert GLFW modifier code into rendercore modifier code
    *
    *  @param[in] key
    *    GLFW key modifier
    *
    *  @return
    *    rendercore key modifier
    */
    // rendercore::KeyModifier fromGLFWModifier(int modifier) const;

protected:
    std::unique_ptr<rendercore::Canvas> m_canvas;      ///< Canvas that controls the rendering onto the window (must NOT be null)
    glm::ivec2                          m_deviceSize;  ///< Window size (real device pixels)
    glm::ivec2                          m_virtualSize; ///< Window size (virtual pixel size)
};


} // namespace glfw
} // namespace rendercore
