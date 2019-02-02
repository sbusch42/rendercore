
#include <rendercore/Image.h>

#include <algorithm>

#include <cppassist/logging/logging.h>
#include <cppassist/memory/make_unique.h>


namespace rendercore
{


unsigned int Image::channels(Format format)
{
    switch (format) {
        case Format::Red:
        case Format::Green:
        case Format::Blue:
        case Format::Red_Integer:
        case Format::Green_Integer:
        case Format::Blue_Integer:
        case Format::Depth_Component:
        case Format::Stencil_Index:
        case Format::Color_Index:
        case Format::Luminance:
            return 1;

        case Format::RG:
        case Format::RG_Integer:
        case Format::Depth_Stencil:
        case Format::Luminance_Alpha:
            return 2;

        case Format::RGB:
        case Format::BGR:
        case Format::RGB_Integer:
        case Format::BGR_Integer:
            return 3;

        case Format::RGBA:
        case Format::BGRA:
        case Format::RGBA_Integer:
        case Format::BGRA_Integer:
            return 4;

        default:
            return 0;
    }
}

unsigned int Image::bytesPerElement(DataType type)
{
    switch (type) {
        case DataType::Byte:
        case DataType::Unsigned_Byte:
            return 1;

        case DataType::Short:
        case DataType::Unsigned_Short:
            return 2;

        case DataType::Int:
        case DataType::Unsigned_Int:
        case DataType::Float:
            return 4;

        case DataType::Double:
            return 8;

        default:
            return 0;
    }
}

bool Image::isCompressed(DataType type)
{
    return (type >= DataType::Compressed);
}

Image::Image()
: m_width(0)
, m_height(0)
, m_format(Format::Unknown)
, m_type(DataType::Unknown)
, m_channels(0)
, m_bytesPerElement(0)
, m_size(0)
, m_data(nullptr)
{
}

Image::Image(unsigned int width, unsigned int height, Format format, DataType type)
: Image()
{
    allocate(width, height, format, type);
}

Image::Image(unsigned int width, unsigned int height, Format format, DataType type, const char * data, unsigned int size)
: Image()
{
    setData(width, height, format, type, data, size);
}

Image::Image(const Image & image)
: Image()
{
    setData(image.width(), image.height(), image.format(), image.type(), image.data(), image.size());
}

Image::Image(Image && image)
: m_width(image.m_width)
, m_height(image.m_height)
, m_format(image.m_format)
, m_type(image.m_type)
, m_channels(image.m_channels)
, m_bytesPerElement(image.m_bytesPerElement)
, m_size(image.m_size)
, m_data(std::move(m_data))
{
}

Image::~Image()
{
}

Image & Image::operator =(Image & image)
{
    setData(image.width(), image.height(), image.format(), image.type(), image.data(), image.size());

    return *this;
}

Image & Image::operator =(Image && image)
{
    initializeImage(image.width(), image.height(), image.format(), image.type(), image.size());
    m_data = std::move(image.m_data);

    return *this;
}

bool Image::empty() const
{
    return m_data == nullptr;
}

unsigned int Image::width() const
{
    return m_width;
}

unsigned int Image::height() const
{
    return m_height;
}

Format Image::format() const
{
    return m_format;
}

DataType Image::type() const
{
    return m_type;
}

unsigned int Image::channels() const
{
    return m_channels;
}

unsigned int Image::bytesPerElement() const
{
    return m_bytesPerElement;
}

bool Image::isCompressed() const
{
    return Image::isCompressed(m_type);
}

unsigned int Image::size() const
{
    return m_size;
}

const char * Image::data() const
{
    return m_data.get();
}

char * Image::data()
{
    return m_data.get();
}

void Image::clear()
{
    m_width           = 0;
    m_height          = 0;
    m_format          = Format::Unknown;
    m_type            = DataType::Unknown;
    m_channels        = 0;
    m_bytesPerElement = 0;
    m_size            = 0;
    m_data            = nullptr;
}

void Image::allocate(unsigned int width, unsigned int height, Format format, DataType type)
{
    // Release old image
    clear();

    // Initialize image information
    initializeImage(width, height, format, type);
    if (m_size == 0) {
        cppassist::critical() << "Image buffer creation failed.";
        return;
    }

    // Create image data
    m_data = cppassist::make_unique<char[]>(m_size);
    if (!m_data) {
        cppassist::critical() << "Image buffer creation failed.";
        return;
    }
}

void Image::setData(unsigned int width, unsigned int height, Format format, DataType type, const char * data, unsigned int size)
{
    // Release old image
    clear();

    // Initialize image information
    initializeImage(width, height, format, type, size);
    if (m_size == 0) {
        cppassist::critical() << "Image buffer creation failed.";
        return;
    }

    // Create image data
    m_data = cppassist::make_unique<char[]>(m_size);
    if (!m_data) {
        cppassist::critical() << "Image buffer creation failed.";
        return;
    }

    // Copy image data
    std::copy_n(data, m_size, m_data.get());
}

void Image::initializeImage(unsigned int width, unsigned int height, Format format, DataType type, unsigned int size)
{
    m_width           = width;
    m_height          = height;
    m_format          = format;
    m_type            = type;
    m_channels        = channels(format);
    m_bytesPerElement = bytesPerElement(type);
    m_size            = size;

    if (m_size == 0 && !isCompressed(m_type)) {
        m_size = m_width * m_height * m_channels * m_bytesPerElement;
    }
}


} // namespace rendercore
