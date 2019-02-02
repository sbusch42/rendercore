
#pragma once


#include <memory>

#include <rendercore/rendercore_api.h>


namespace rendercore
{


/**
*  @brief
*    Image formats
*/
enum class Format : unsigned int
{
    Unknown = 0
  , Red
  , Green
  , Blue
  , Red_Integer
  , Green_Integer
  , Blue_Integer
  , Depth_Component
  , Stencil_Index
  , Color_Index
  , Luminance
  , RG
  , RG_Integer
  , Depth_Stencil
  , Luminance_Alpha
  , RGB
  , BGR
  , RGB_Integer
  , BGR_Integer
  , RGBA
  , BGRA
  , RGBA_Integer
  , BGRA_Integer
};

/**
*  @brief
*    Data types
*/
enum class DataType : unsigned int
{
    Unknown = 0

  , Byte
  , Unsigned_Byte
  , Short
  , Unsigned_Short
  , Int
  , Unsigned_Int
  , Float
  , Double

  , Compressed
  , Compressed_Red_RGTC1 = Compressed
  , Compressed_Signed_Red_RGTC1
  , Compressed_RG_RGTC2
  , Compressed_Signed_RG_RGTC2
  , Compressed_RGBA_BPTC_Unorm
  , Compressed_RGB_BPTC_Signed_Float
  , Compressed_RGB_BPTC_Unsigned_Float
  , Compressed_RGB_S3TC_DXT1
  , Compressed_RGBA_S3TC_DXT1
  , Compressed_RGBA_S3TC_DXT3
  , Compressed_RGBA_S3TC_DXT5
};

/**
*  @brief
*    Image class that holds image data and meta information about images
*/
class RENDERCORE_API Image
{
public:
    /**
    *  @brief
    *    Get number of color channels for given image format
    *
    *  @param[in] format
    *    Format
    *
    *  @return
    *    Number of color channels
    */
    static unsigned int channels(Format format);

    /**
    *  @brief
    *    Get number of bytes for a given data type
    *
    *  @param[in] type
    *    Data type
    *
    *  @return
    *    Number of bytes per element
    */
    static unsigned int bytesPerElement(DataType type);

    /**
    *  @brief
    *    Check if data type refers to a compressed format
    *
    *  @param[in] type
    *    Data type
    *
    *  @return
    *    'true' if this is a compressed format, else 'false'
    */
    static bool isCompressed(DataType type);

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
    *  @param[in] format
    *    Image format
    *  @param[in] type
    *    Data type
    *
    *  @remarks
    *    Allocates new image memory, unless type specifies a compressed format.
    *
    *  @see allocate
    */
    Image(unsigned int width, unsigned int height, Format format, DataType type);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] width
    *    Image width
    *  @param[in] height
    *    Image height
    *  @param[in] format
    *    Image format
    *  @param[in] type
    *    Data type
    *  @param[in] data
    *    Image data (must NOT be null!)
    *  @param[in] size
    *    Image data size
    *
    *  @remarks
    *    Allocates new image memory and copies the content of data.
    *
    *  @see setData
    */
    Image(unsigned int width, unsigned int height, Format format, DataType type, const char * data, unsigned int size);

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
    *    Get image format
    *
    *  @return
    *    Image format
    */
    Format format() const;

    /**
    *  @brief
    *    Get data type
    *
    *  @return
    *    Data type
    */
    DataType type() const;

    /**
    *  @brief
    *    Get number of color channels
    *
    *  @return
    *    Number of color channels
    */
    unsigned int channels() const;

    /**
    *  @brief
    *    Get number of bytes per element
    *
    *  @return
    *    Number of bytes per element
    */
    unsigned int bytesPerElement() const;

    /**
    *  @brief
    *    Check if image has compressed format
    *
    *  @return
    *    'true' if image has a compressed format, else 'false'
    */
    bool isCompressed() const;

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
    *    Allocate image memory
    *
    *  @param[in] width
    *    Image width
    *  @param[in] height
    *    Image height
    *  @param[in] format
    *    Image format
    *  @param[in] type
    *    Data type
    *
    *  @remarks
    *    Any existing image data is deleted.
    */
    void allocate(unsigned int width, unsigned int height, Format format, DataType type);

    /**
    *  @brief
    *    Create image from existing image data
    *
    *  @param[in] width
    *    Image width
    *  @param[in] height
    *    Image height
    *  @param[in] format
    *    Image format
    *  @param[in] type
    *    Data type
    *  @param[in] data
    *    Pointer to image data (must NOT be null!)
    *  @param[in] size
    *    Image data size
    *
    *  @remarks
    *    This allocates new image memory and copies the content of data.
    *    Any existing image data is deleted.
    */
    void setData(unsigned int width, unsigned int height, Format format, DataType type, const char * data, unsigned int size);

protected:
    /**
    *  @brief
    *    Set image information
    *
    *  @param[in] width
    *    Image width
    *  @param[in] height
    *    Image height
    *  @param[in] format
    *    Image format
    *  @param[in] type
    *    Data type
    *  @param[in] size
    *    Image data size (if 0, size is determined automatically)
    *
    *  @remarks
    *    This function only sets the image information, it does not allocate
    *    or set the image data. If size == 0, the size is determined based
    *    on the format and type.
    */
    void initializeImage(unsigned int width, unsigned int height, Format format, DataType type, unsigned int size = 0);

protected:
    unsigned int            m_width;           ///< Image width
    unsigned int            m_height;          ///< Image height
    Format                  m_format;          ///< Image format
    DataType                m_type;            ///< Data type
    unsigned int            m_channels;        ///< Number of color channels
    unsigned int            m_bytesPerElement; ///< Bytes per element
    unsigned int            m_size;            ///< Size of image data (in bytes)
    std::unique_ptr<char[]> m_data;            ///< Image data (can be null)
};


} // namespace rendercore
