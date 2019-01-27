
#pragma once


#include <cppexpose/signal/Signal.h>

#include <rendercore/base/TimerManager.h>


namespace rendercore
{


/**
*  @brief
*    Class that manages the rendering environment
*/
class RENDERCORE_API Environment
{
public:
    cppexpose::Signal<int> exitApplication; ///< Called when application shall exit

public:
    /**
    *  @brief
    *    Constructor
    */
    Environment();

    /**
    *  @brief
    *    Destructor
    */
    ~Environment();
};


} // namespace rendercore
