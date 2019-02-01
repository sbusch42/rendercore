
#pragma once


#include <rendercore/rendercore_api.h>


namespace rendercore
{


/**
*  @brief
*    Abstract base class for contexts
*
*    This base class describes a common interface for contexts of any kind.
*    It is meant especially for rendering contexts, such as OpenGL, but can
*    also be used for other kinds of contexts, such as CUDA, OpenAL, etc.
*/
class RENDERCORE_API AbstractContext
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractContext();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractContext();

    /**
    *  @brief
    *    Activate context
    */
    virtual void use() const = 0;

    /**
    *  @brief
    *    Release context
    */
    virtual void release() const = 0;
};


} // namespace rendercore
