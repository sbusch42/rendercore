
#pragma once


#include <vector>
#include <string>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace globjects
{
    class Texture;
}


namespace rendercore
{


class Environment;


namespace opengl
{


/**
*  @brief
*    File loader for '.glraw' files
*/
class RENDERCORE_OPENGL_API GlrawTextureLoader
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] environment
    *    Environment to which the loader belongs (must NOT be null!)
    */
    GlrawTextureLoader(Environment * environment);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~GlrawTextureLoader();

    bool canLoad(const std::string & ext) const;
    std::vector<std::string> loadingTypes() const;
    std::string allLoadingTypes() const;
    globjects::Texture * load(const std::string & filename) const;

protected:
    /**
    *  @brief
    *    Create Texture from .glraw file
    *
    *  @param[in] filename
    *    path of the .glraw file
    *
    *  @return
    *    Loaded texture, null on error
    */
    globjects::Texture * loadGLRawImage(const std::string & filename) const;

    /**
    *  @brief
    *    Create Texture from .raw file
    *
    *  @param[in] filename
    *    path of the .raw file
    *
    *  @return
    *    Loaded texture, null on error
    */
    globjects::Texture * loadRawImage(const std::string & filename) const;

protected:
    std::vector<std::string> m_extensions; ///< List of supported file extensions (e.g., ".bmp")
    std::vector<std::string> m_types;      ///< List of supported file types (e.g., "bmp image (*.bmp)")
};


} // namespace opengl
} // namespace rendercore
