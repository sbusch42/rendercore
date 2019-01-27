
#pragma once


#include <memory>

#include <rendercore-opengl/AbstractGLContext.h>


namespace rendercore
{
namespace opengl
{


class GLContextFormat;


/**
*  @brief
*    Abstract base class for OpenGL context factories
*
*    A context factory is used to create OpenGL contexts.
*    It must be provided by the windowing backend and can
*    be accessed via Environment.
*/
class RENDERCORE_OPENGL_API AbstractGLContextFactory
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractGLContextFactory();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractGLContextFactory();

    /**
    *  @brief
    *    Create best possible OpenGL context for a given format
    *
    *  @param[in] format
    *    Desired OpenGL format
    *
    *  @return
    *    OpenGL context
    *
    *  @remarks
    *    This function tries to create a context that fits the desired
    *    format as good as possible. It internally uses createContext()
    *    to create the actual contexts, determine maximum versions etc.
    *    If a major version lesser 3 is provided, the system tries to
    *    create a context with the maximum available OpenGL version.
    */
    std::unique_ptr<AbstractGLContext> createBestContext(const GLContextFormat & format) const;

    /**
    *  @brief
    *    Create OpenGL context with the given format
    *
    *  @param[in] format
    *    Desired OpenGL format
    *
    *  @return
    *    OpenGL context
    *
    *  @remarks
    *    Format has to contain valid major and minor OpenGL version.
    *    Platform-dependent defaults are expected to be set beforehand
    *    (e.g., macOS with OpenGL 3.2 Core FC).
    */
    virtual std::unique_ptr<AbstractGLContext> createContext(const GLContextFormat & format) const = 0;
};


} // namespace opengl
} // namespace rendercore
