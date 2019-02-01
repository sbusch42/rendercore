
#include <rendercore/Image.h>

#include <algorithm>

#include <cppassist/logging/logging.h>
#include <cppassist/memory/make_unique.h>


namespace rendercore
{


int Image::channels(Format format)
{
    switch (format) {
        case Format::Red:             return 1;
        case Format::Green:           return 1;
        case Format::Blue:            return 1;
        case Format::Red_Integer:     return 1;
        case Format::Green_Integer:   return 1;
        case Format::Blue_Integer:    return 1;
        case Format::Depth_Component: return 1;
        case Format::Stencil_Index:   return 1;
        case Format::Color_Index:     return 1;
        case Format::Luminance:       return 1;

        case Format::RG:              return 2;
        case Format::RG_Integer:      return 2;
        case Format::Depth_Stencil:   return 2;
        case Format::Luminance_Alpha: return 2;

        case Format::RGB:             return 3;
        case Format::BGR:             return 3;
        case Format::RGB_Integer:     return 3;
        case Format::BGR_Integer:     return 3;

        case Format::RGBA:            return 4;
        case Format::BGRA:            return 4;
        case Format::RGBA_Integer:    return 4;
        case Format::BGRA_Integer:    return 4;

        default:                      return 0;
    }
}

int Image::bytes(DataType type)
{
    switch (type) {
        case DataType::Byte:           return 1;
        case DataType::Unsigned_Byte:  return 1;
        case DataType::Short:          return 2;
        case DataType::Unsigned_Short: return 2;
        case DataType::Int:            return 4;
        case DataType::Unsigned_Int:   return 4;
        case DataType::Float:          return 4;
        case DataType::Double:         return 8;
        default:                       return 0;
    }
}

Image::Image()
: m_width(0)
, m_height(0)
, m_format(Format::Invalid)
, m_type(DataType::Invalid)
, m_channels(0)
, m_bytes(0)
, m_dataSize(0)
, m_data(nullptr)
{
}

Image::Image(int width, int height, Format format, DataType type)
: Image()
{
    allocate(width, height, format, type);
}

Image::Image(int width, int height, Format format, DataType type, const char * data)
: Image()
{
    copyImage(width, height, format, type, data);
}

Image::Image(int width, int height, Format format, DataType type, std::unique_ptr<char[]> && data)
: Image()
{
    setData(width, height, format, type, std::move(data));
}

Image::Image(const Image & other)
: Image()
{
    copyImage(other.width(), other.height(), other.format(), other.type(), other.data());
}

Image::Image(Image && other)
: Image()
{
    swap(*this, other);
}

Image::~Image()
{
}

Image & Image::operator=(Image other)
{
    swap(*this, other);

    return *this;
}

bool Image::empty() const
{
    return m_data == nullptr;
}

int Image::width() const
{
    return m_width;
}

int Image::height() const
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

int Image::channels() const
{
    return m_channels;
}

int Image::bytes() const
{
    return m_bytes;
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
    m_width    = 0;
    m_height   = 0;
    m_format   = Format::Invalid;
    m_type     = DataType::Invalid;
    m_channels = 0;
    m_bytes    = 0;
    m_dataSize = 0;
    m_data     = nullptr;
}

void Image::allocate(int width, int height, Format format, DataType type)
{
    clear();

    initializeImage(width, height, format, type);

    if (m_dataSize == 0) {
        cppassist::critical() << "Image buffer creation failed.";
        return;
    }

    m_data = cppassist::make_unique<char[]>(m_dataSize);
}

void Image::copyImage(int width, int height, Format format, DataType type, const char * data)
{
    clear();

    allocate(width, height, format, type);

    if (m_data == nullptr) {
        cppassist::critical() << "Image buffer creation failed.";
        return;
    }

    std::copy_n(data, m_dataSize, m_data.get());
}

void Image::setData(int width, int height, Format format, DataType type, std::unique_ptr<char[]> && data)
{
    clear();

    initializeImage(width, height, format, type);

    m_data = m_dataSize ? std::move(data) : nullptr;
}

void swap(Image & first, Image & second) noexcept
{
    using std::swap;

    swap(first.m_data,     second.m_data);
    swap(first.m_dataSize, second.m_dataSize);
    swap(first.m_width,    second.m_width);
    swap(first.m_height,   second.m_height);
    swap(first.m_channels, second.m_channels);
    swap(first.m_bytes,    second.m_bytes);
    swap(first.m_format,   second.m_format);
    swap(first.m_type,     second.m_type);
}

void Image::initializeImage(int width, int height, Format format, DataType type)
{
    m_width    = width;
    m_height   = height;
    m_channels = channels(format);
    m_bytes    = bytes(type);
    m_dataSize = m_width * m_height * m_channels * m_bytes;
    m_format   = format;
    m_type     = type;
}


} // namespace rendercore
