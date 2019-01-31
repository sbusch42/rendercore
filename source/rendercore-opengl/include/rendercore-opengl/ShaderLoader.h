
#pragma once


#include <memory>
#include <string>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace globjects
{
    class Shader;
}


namespace rendercore
{


class Environment;


namespace opengl
{


/**
*  @brief
*    Shader loader
*/
class RENDERCORE_OPENGL_API ShaderLoader
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ShaderLoader(Environment * environment);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ShaderLoader();

    /**
    *  @brief
    *    Load shader
    *
    *  @param[in] filename
    *    Path to file
    *
    *  @return
    *    Shader (can be null)
    */
    std::unique_ptr<globjects::Shader> load(const std::string & filename) const;
};


} // namespace opengl
} // namespace rendercore
