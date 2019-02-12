
#pragma once


#include <memory>
#include <string>

#include <rendercore/Image.h>


namespace rendercore
{


/**
*  @brief
*    Image loader from .raw or .glraw files
*/
class RENDERCORE_API ImageLoader
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ImageLoader();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ImageLoader();

    /**
    *  @brief
    *    Load image
    *
    *  @param[in] filename
    *    Path to file
    *
    *  @return
    *    Image (can be null)
    */
    std::unique_ptr<Image> load(const std::string & filename) const;

protected:
    /**
    *  @brief
    *    Load image from common file formats
    *
    *  @param[in] filename
    *    path of the image file
    *
    *  @return
    *    Loaded image, null on error
    */
    std::unique_ptr<Image> loadCommonImage(const std::string & filename) const;

    /**
    *  @brief
    *    Create image from .glraw file
    *
    *  @param[in] filename
    *    path of the .glraw file
    *
    *  @return
    *    Loaded image, null on error
    */
    std::unique_ptr<Image> loadGLRawImage(const std::string & filename) const;

    /**
    *  @brief
    *    Create image from .raw file
    *
    *  @param[in] filename
    *    path of the .raw file
    *
    *  @return
    *    Loaded image, null on error
    */
    std::unique_ptr<Image> loadRawImage(const std::string & filename) const;
};


} // namespace rendercore
