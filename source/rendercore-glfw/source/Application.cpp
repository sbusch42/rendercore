
// [TODO] Review
#include <rendercore-glfw/Application.h>

#include <iostream>

#include <cassert>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <rendercore/base/Environment.h>

#include <rendercore-glfw/Window.h>


namespace rendercore_glfw
{


Application * Application::s_app = nullptr;


int Application::init()
{
    return glfwInit();
}

void Application::quit(int code)
{
    // An application needs to be initialized already
    assert(s_app);

    // Stop application
    s_app->stop(code);
}

void Application::wakeup()
{
    // Post event to wake up the mainloop
    glfwPostEmptyEvent();
}

Application::Application(rendercore::Environment * environment, int &, char **)
: m_environment(environment)
, m_running(false)
, m_exitCode(0)
{
    // Make sure that no application object has already been instanciated
    assert(!s_app);
    s_app = this;

    // Connect to exit-signal
    environment->exitApplication.connect([] (int exitCode)
    {
        Application::quit(exitCode);
    });
}

Application::~Application()
{
    // Deregister application
    s_app = nullptr;
}

int Application::run()
{
    // Abort if application is already running
    if (m_running)
    {
        return 1;
    }

    // Start application
    m_running  = true;
    m_exitCode = 0;

    // Execute main loop
    while (m_running)
    {
        std::cout << "mainloop!" << std::endl;

        // Wait until events arrive.
        // To unlock the main loop, call wakeup().
        glfwWaitEvents();
        processEvents();
    }

    // Deinitialize GLFW
    glfwTerminate();

    // Return with exit code
    return m_exitCode;
}

void Application::stop(int code)
{
    // Stop application, return the given exit code
    m_exitCode = code;
    m_running  = false;
}

bool Application::isRunning() const
{
    return m_running;
}

int Application::exitCode()
{
    return m_exitCode;
}

void Application::processEvents()
{
    // Get messages for all windows
    for (Window * window : Window::instances())
    {
        // Update timing
        window->idle();

        // If window needs updating, let it send an udate event
        window->updateRepaintEvent();

        // Process all events for the window
        if (window->hasPendingEvents()) {
            window->processEvents();
        }
    }
}


} // namespace rendercore_glfw
