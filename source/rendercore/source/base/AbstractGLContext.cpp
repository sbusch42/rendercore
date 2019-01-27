
#include <rendercore/base/AbstractGLContext.h>

#include <globjects/globjects.h>
#include <globjects/DebugMessage.h>


namespace rendercore
{


AbstractGLContext::AbstractGLContext()
{
}

AbstractGLContext::~AbstractGLContext()
{
}

const GLContextFormat & AbstractGLContext::format() const
{
    return m_format;
}

void AbstractGLContext::initializeBindings(glbinding::GetProcAddress functionPointerResolver)
{
    // Initialize globjects and glbinding
    globjects::init(functionPointerResolver);

    // Enable debug messages
#ifndef NDEBUG
    globjects::DebugMessage::enable(true);
#endif
}


} // namespace rendercore
