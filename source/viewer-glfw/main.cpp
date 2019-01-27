

#include <memory>

#include <cppassist/memory/make_unique.h>
#include <cppassist/logging/logging.h>
#include <cppassist/cmdline/ArgumentParser.h>

#include <rendercore/rendercore.h>
#include <rendercore/base/Environment.h>
#include <rendercore/base/Canvas.h>
#include <rendercore/base/GLContextUtils.h>
#include <rendercore/base/ExampleRenderer.h>

#include <rendercore-glfw/Application.h>
#include <rendercore-glfw/RenderWindow.h>
#include <rendercore-glfw/GLContext.h>


using namespace rendercore;
using namespace rendercore_glfw;


int main(int argc, char * argv[])
{
    // Read command line options
    cppassist::ArgumentParser argumentParser;
    argumentParser.parse(argc, argv);

    const auto contextString = argumentParser.value("--context");

    // Create environment
    Environment environment;

    // Initialize GLFW
    Application::init();
    Application app(&environment, argc, argv);

    // Create render window
    RenderWindow window(&environment);

    // Specify desired context format
    rendercore::GLContextFormat format;
    format.setVersion(3, 2);
    format.setProfile(rendercore::GLContextFormat::Profile::Core);
    format.setForwardCompatible(true);
    if (!contextString.empty())
    {
        // Set format from command line parameter
        if (!format.initializeFromString(contextString))
        {
            return 1;
        }
    }

    // Create window
    window.setContextFormat(format);
    window.setTitle("rendercore viewer");
    window.setSize(1280, 720);
    if (!window.create())
    {
        return 1;
    }

    // Create renderer
    window.canvas()->setRenderer(cppassist::make_unique<ExampleRenderer>(&environment));

    // Initialize context, print context info
    window.context()->use();
//  window.context()->setSwapInterval(Context::SwapInterval::VerticalSyncronization);
    cppassist::info() << std::endl
        << "OpenGL Version:  " << GLContextUtils::version() << std::endl
        << "OpenGL Profile:  " << GLContextUtils::profile() << std::endl
        << "OpenGL Vendor:   " << GLContextUtils::vendor() << std::endl
        << "OpenGL Renderer: " << GLContextUtils::renderer() << std::endl;
    window.context()->release();

    // Display window
    window.show();

    // Run main loop
    return app.run();
}
