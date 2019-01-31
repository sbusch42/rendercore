
#pragma once


#include <memory>
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
*    Texture loader from .raw or .glraw files
*/
class RENDERCORE_OPENGL_API TextureLoader
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] environment
    *    Environment to which the loader belongs (must NOT be null!)
    */
    TextureLoader(Environment * environment);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TextureLoader();

    /**
    *  @brief
    *    Load texture
    *
    *  @param[in] filename
    *    Path to file
    *
    *  @return
    *    Texture (can be null)
    */
    std::unique_ptr<globjects::Texture> load(const std::string & filename) const;

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
    std::unique_ptr<globjects::Texture> loadGLRawImage(const std::string & filename) const;

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
    std::unique_ptr<globjects::Texture> loadRawImage(const std::string & filename) const;
};


} // namespace opengl
} // namespace rendercore
