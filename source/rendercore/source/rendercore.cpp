
#include <rendercore/rendercore.h>

#include <cpplocate/cpplocate.h>


namespace
{


std::string determineDataPath()
{
    std::string path = cpplocate::locatePath("data/rendercore", "share/rendercore", reinterpret_cast<void *>(&rendercore::dataPath));
    if (path.empty()) path = "./data";
    else              path = path + "/data";

    return path;
}


}


namespace rendercore
{


const std::string & dataPath()
{
    static const auto path = determineDataPath();

    return path;
}


} // namespace rendercore
