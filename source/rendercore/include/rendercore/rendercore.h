
#pragma once


#include <string>

#include <rendercore/rendercore_api.h>


namespace rendercore
{


/**
*  @brief
*    Get path to data files
*
*  @return
*    Path to data files, or '' if data files couldn't be found
*/
RENDERCORE_API const std::string & dataPath();


} // namespace rendercore
