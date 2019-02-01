
#pragma once


#include <memory>

#include <rendercore/rendercore_api.h>


namespace rendercore
{


/**
*  @brief
*    Image formats
*/
enum class Format : uint32_t
{
    Invalid = 0
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
enum class DataType : uint32_t
{
    Invalid = 0
  , Byte
  , Unsigned_Byte
  , Short
  , Unsigned_Short
  , Int
  , Unsigned_Int
  , Float
  , Double
};

/**
*  @brief
*    Image class that holds image data and meta information.
*
*    Currently supports format RGB24.
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
    static int channels(Format format);

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
    static int bytes(DataType type);

public:
    /**
    *  @brief
    *    Constructor for an empty image
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
    *    Allocates the necessary image data memory.
    *
    *  @see createBuffer
    */
    Image(int width, int height, Format format, DataType type);

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
    *    Pointer to image data (must NOT be null!)
    *
    *  @remarks
    *    This allocates new image memory and copies the content of data.
    *
    *  @see createBuffer
    */
    Image(int width, int height, Format format, DataType type, const char * data);

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
    *    Pointer to image data (must NOT be null!)
    *
    *  @remarks
    *    This does NOT allocate own memory.
    *    The ownership of data is transferred to the Image object.
    */
    Image(int width, int height, Format format, DataType type, std::unique_ptr<char[]> && data);

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] other
    *    Source image
    */
    Image(const Image & other);

    /**
    *  @brief
    *    Move constructor
    *
    *  @param[in] other
    *    Source image
    */
    Image(Image && other);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Image();

    /**
    *  @brief
    *    Assignment operator
    *
    *  @param[in] other
    *    Source image
    *
    *  @return
    *    Reference to this object

    *  @remarks
    *    https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    */
    Image & operator =(Image other);

    /**
    *  @brief
    *    Check if image is empty
    *
    *  @return
    *    'true' if the image is empty, else 'false'
    *
    *  @remarks
    *    An empty image has all parameters set to zero and no allocated data.
    */
    bool empty() const;

    /**
    *  @brief
    *    Get width
    *
    *  @return
    *    Image width
    */
    int width() const;

    /**
    *  @brief
    *    Get height
    *
    *  @return
    *    Image height
    */
    int height() const;

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
    int channels() const;

    /**
    *  @brief
    *    Get number of bytes per element
    *
    *  @return
    *    Number of bytes per element
    */
    int bytes() const;

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
    void allocate(int width, int height, Format format, DataType type);

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
    *
    *  @remarks
    *    This allocates new image memory and copies the content of data.
    *    The ownership of data remains at the caller.
    *    Any existing image data is deleted.
    */
    void copyImage(int width, int height, Format format, DataType type, const char * data);

    /**
    *  @brief
    *    Set image data
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
    *
    *  @remarks
    *    This does NOT allocate own memory.
    *    The ownership of data is transferred to the Image object.
    *    Any existing image data is deleted.
    */
    void setData(int width, int height, Format format, DataType type, std::unique_ptr<char[]> && data);

    /**
    *  @brief
    *    Swap function for copy-and-swap idiom
    *
    *  @param[in] first
    *    Image
    *  @param[in] second
    *    Image
    *
    *  @remarks
    *    See https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    */
    friend void swap(Image & first, Image & second) noexcept;

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
    *
    *  @remarks
    *    This function only sets the image information, it does not
    *    allocate or set the image data.
    */
    void initializeImage(int width, int height, Format format, DataType type);

protected:
    int                     m_width;    ///< Image width (0 if empty)
    int                     m_height;   ///< Image height (0 if empty)
    Format                  m_format;   ///< Image format
    DataType                m_type;     ///< Data type
    int                     m_channels; ///< Number of color channels (0 if empty)
    int                     m_bytes;    ///< Bytes per element (0 if empty)
    int                     m_dataSize; ///< Size of image data (0 if empty)
    std::unique_ptr<char[]> m_data;     ///< Image data (can be null)
};


} // namespace rendercore
