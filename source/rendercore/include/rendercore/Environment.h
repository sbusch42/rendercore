
#pragma once


#include <rendercore/Signal.h>


namespace rendercore
{


/**
*  @brief
*    Class that manages the rendering environment
*/
class RENDERCORE_API Environment
{
public:
    Signal<int> exitApplication; ///< Called when application shall exit

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
