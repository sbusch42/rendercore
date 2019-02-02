
#pragma once


#include <memory>

#include <rendercore/rendercore_api.h>


namespace rendercore
{


/**
*  @brief
*    Image class that holds image data and meta information about images
*
*  @remarks
*    The image class acts just as a container for image data, it does not
*    examine or analyze the data it is given. Therefore, the image data
*    and meta information have to be set from the outside and are assumed
*    to be correct (e.g., the image class will not check if the data size
*    corresponds to the given size and format of the image).
*
*    The image format and data type values are compatible with OpenGL enums
*    and are not interpreted by the image class.
*/
class RENDERCORE_API Image
{
public:
    /**
    *  @brief
    *    Constructor (empty image)
    */
    Image();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] width
    *    Image width
    *  @param[in] height
    *    Image height
    *  @param[in] depth
    *    Image depth
    *  @param[in] format
    *    Image format (OpenGL enum)
    *  @param[in] type
    *    Data type (OpenGL enum)
    *  @param[in] size
    *    Image data size
    *  @param[in] data
    *    Image data (must NOT be null!)
    *
    *  @remarks
    *    Allocates new image memory and copies the content of data.
    *
    *  @see setData
    */
    Image(unsigned int width, unsigned int height, unsigned int depth, unsigned int format, unsigned int type, unsigned int size, const char * data);

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] image
    *    Source image
    */
    Image(const Image & image);

    /**
    *  @brief
    *    Move constructor
    *
    *  @param[in] image
    *    Source image
    */
    Image(Image && image);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Image();

    /**
    *  @brief
    *    Copy operator
    *
    *  @param[in] image
    *    Source image
    *
    *  @return
    *    Reference to this object
    */
    Image & operator =(Image & image);

    /**
    *  @brief
    *    Move operator
    *
    *  @param[in] image
    *    Source image
    *
    *  @return
    *    Reference to this object
    */
    Image & operator =(Image && image);

    /**
    *  @brief
    *    Check if image is empty
    *
    *  @return
    *    'true' if the image is empty, else 'false'
    *
    *  @remarks
    *    An empty image has no data.
    */
    bool empty() const;

    /**
    *  @brief
    *    Get width
    *
    *  @return
    *    Image width
    */
    unsigned int width() const;

    /**
    *  @brief
    *    Get height
    *
    *  @return
    *    Image height
    */
    unsigned int height() const;

    /**
    *  @brief
    *    Get depth
    *
    *  @return
    *    Image depth
    */
    unsigned int depth() const;

    /**
    *  @brief
    *    Get image format
    *
    *  @return
    *    Image format (OpenGL enum)
    */
    unsigned int format() const;

    /**
    *  @brief
    *    Get data type
    *
    *  @return
    *    Data type (OpenGL enum)
    */
    unsigned int dataType() const;

    /**
    *  @brief
    *    Get image size
    *
    *  @return
    *    Image size (in bytes)
    */
    unsigned int size() const;

    /**
    *  @brief
    *    Get image data
    *
    *  @return
    *    Pointer to raw image data (can be null)
    */
    const char * data() const;

    /**
    *  @brief
    *    Get image data
    *
    *  @return
    *    Pointer to raw image data (can be null)
    */
    char * data();

    /**
    *  @brief
    *    Clear image
    *
    *  @remarks
    *    Releases all data and resets to an empty image.
    *
    *  @see empty()
    */
    void clear();

    /**
    *  @brief
    *    Create image from image data
    *
    *  @param[in] width
    *    Image width
    *  @param[in] height
    *    Image height
    *  @param[in] depth
    *    Image depth
    *  @param[in] format
    *    Image format (OpenGL enum)
    *  @param[in] type
    *    Data type (OpenGL enum)
    *  @param[in] size
    *    Image data size
    *  @param[in] data
    *    Pointer to image data (must NOT be null!)
    *
    *  @remarks
    *    This allocates new image memory and copies the content of data.
    *    Any existing image data is deleted.
    */
    void setData(unsigned int width, unsigned int height, unsigned int depth, unsigned int format, unsigned int type, unsigned int size, const char * data);

protected:
    /**
    *  @brief
    *    Set image information
    *
    *  @param[in] width
    *    Image width
    *  @param[in] height
    *    Image height
    *  @param[in] depth
    *    Image depth
    *  @param[in] format
    *    Image format (OpenGL enum)
    *  @param[in] type
    *    Data type (OpenGL enum)
    *  @param[in] size
    *    Image data size
    */
    void initializeImage(unsigned int width, unsigned int height, unsigned int depth, unsigned int format, unsigned int type, unsigned int size);

protected:
    unsigned int            m_width;  ///< Image width
    unsigned int            m_height; ///< Image height
    unsigned int            m_depth;  ///< Image depth
    unsigned int            m_format; ///< Image format (OpenGL enum)
    unsigned int            m_type;   ///< Data type (OpenGL enum)
    unsigned int            m_size;   ///< Size of image data (in bytes)
    std::unique_ptr<char[]> m_data;   ///< Image data (can be null)
};


} // namespace rendercore
