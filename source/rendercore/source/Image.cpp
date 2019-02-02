
#include <rendercore/Image.h>

#include <algorithm>

#include <cppassist/logging/logging.h>
#include <cppassist/memory/make_unique.h>


namespace rendercore
{


Image::Image()
: m_width(0)
, m_height(0)
, m_depth(0)
, m_format(0)
, m_type(0)
, m_size(0)
, m_data(nullptr)
{
}

Image::Image(unsigned int width, unsigned int height, unsigned int depth, unsigned int format, unsigned int type, unsigned int size, const char * data)
: Image()
{
    setData(width, height, depth, format, type, size, data);
}

Image::Image(const Image & image)
: Image()
{
    setData(image.width(), image.height(), image.depth(), image.format(), image.dataType(), image.size(), image.data());
}

Image::Image(Image && image)
: m_width(image.m_width)
, m_height(image.m_height)
, m_depth(image.m_depth)
, m_format(image.m_format)
, m_type(image.m_type)
, m_size(image.m_size)
, m_data(std::move(image.m_data))
{
}

Image::~Image()
{
}

Image & Image::operator =(Image & image)
{
    setData(image.width(), image.height(), image.depth(), image.format(), image.dataType(), image.size(), image.data());

    return *this;
}

Image & Image::operator =(Image && image)
{
    initializeImage(image.width(), image.height(), image.depth(), image.format(), image.dataType(), image.size());
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

unsigned int Image::depth() const
{
    return m_depth;
}

unsigned int Image::format() const
{
    return m_format;
}

unsigned int Image::dataType() const
{
    return m_type;
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
    m_width  = 0;
    m_height = 0;
    m_depth  = 0;
    m_format = 0;
    m_type   = 0;
    m_size   = 0;
    m_data   = nullptr;
}

void Image::setData(unsigned int width, unsigned int height, unsigned int depth, unsigned int format, unsigned int type, unsigned int size, const char * data)
{
    // Release old image
    clear();

    // Initialize image information
    initializeImage(width, height, depth, format, type, size);
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

void Image::initializeImage(unsigned int width, unsigned int height, unsigned int depth, unsigned int format, unsigned int type, unsigned int size)
{
    m_width  = width;
    m_height = height;
    m_depth  = depth;
    m_format = format;
    m_type   = type;
    m_size   = size;
}


} // namespace rendercore
