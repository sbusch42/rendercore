
#pragma once


#include <vector>
#include <string>
#include <unordered_map>

#include <cppexpose/plugin/plugin_api.h>

#include <glbinding/gl/enum.h>

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
*
*  Supported options:
*    none
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

    bool canLoad(const std::string & ext) const;
    std::vector<std::string> loadingTypes() const;
    std::string allLoadingTypes() const;
    globjects::Shader * load(const std::string & filename) const;

protected:
    std::vector<std::string> m_extensions; ///< List of supported file extensions (e.g., ".bmp")
    std::vector<std::string> m_types;      ///< List of supported file types (e.g., "bmp image (*.bmp)")

    const std::unordered_map<std::string, gl::GLenum> m_extensionToType; ///< Mapping of file extension to GLenum type
};


} // namespace opengl
} // namespace rendercore
