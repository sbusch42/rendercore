
// [TODO] Review
#pragma once


#include <rendercore-glfw/rendercore-glfw_api.h>


namespace rendercore
{
    class Environment;
}


namespace rendercore_glfw
{


/**
*  @brief
*    Class representing the main message loop
*
*    The Application class is a singleton that has to be instanciated exactly
*    once in an application. It controls the main message loop for all windows
*    (instances of rendercore_glfw::Window).
*/
class RENDERCORE_GLFW_API Application
{
public:
    /**
    *  @brief
    *    Initialize GLFW
    *
    *  @return
    *    Return code (0 for no error, > 0 for error)
    */
    static int init();

    /**
    *  @brief
    *    Quit the currently running application
    *
    *  @param[in] code
    *    Exit code (0 for no error, > 0 for error)
    *
    *  @remarks
    *    Stops the application that is currently running.
    *    An instance of Application must have been created before calling this method.
    */
    static void quit(int code = 0);

    /**
    *  @brief
    *    Wakeup main loop
    */
    static void wakeup();


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] environment
    *    Environment (must NOT be null!)
    *  @param[in] argc
    *    Argument count (pass on parameter from the main function)
    *  @param[in] argv
    *    Argument list (pass on parameter from the main function)
    */
    Application(rendercore::Environment * environment, int & argc, char ** argv);

    /**
    *  @brief
    *    Destructor
    */
    ~Application();

    /**
    *  @brief
    *    Run the main loop
    *
    *    Execute the message loop for the application.
    *    This function will block and run as long as the message
    *    loop is running. To stop the message loop, stop() has to
    *    be called on the Application object.
    *
    *  @return
    *    Exit code (0 for no error, > 0 for error)
    */
    int run();

    /**
    *  @brief
    *    Stop the application
    *
    *  @param[in] code
    *    Exit code (0 for no error, > 0 for error)
    */
    void stop(int code = 0);

    /**
    *  @brief
    *    Check if the application is currently running
    *
    *  @return
    *    'true' if application is currently running, else 'false'
    */
    bool isRunning() const;

    /**
    *  @brief
    *    Get exit code that has currently been set
    *
    *  @return
    *    Exit code (0 for no error, > 0 for error)
    */
    int exitCode();


protected:
    /**
    *  @brief
    *    Process events that have been received
    */
    void processEvents();


protected:
    static Application * s_app; ///< Pointer to the current application instance, can be nullptr


protected:
    rendercore::Environment * m_environment; ///< Environment
    bool                      m_running;     ///< 'true' if application is currently running, else 'false'
    int                       m_exitCode;    ///< Exit code (0 for no error, > 0 for error)
};


} // namespace rendercore_glfw
