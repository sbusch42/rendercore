
#pragma once


#include <rendercore/rendercore_api.h>


namespace rendercore
{


/**
*  @brief
*    Class that manages virtual timing
*/
class RENDERCORE_API TimerManager
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TimerManager();

    /**
    *  @brief
    *    Destructor
    */
    ~TimerManager();

    /**
    *  @brief
    *    Update virtual timer
    */
    void update();
};


} // namespace rendercore
