
#include <rendercore/ImageLoader.h>

#include <map>

#include <cppfs/FilePath.h>

#include <cppassist/memory/make_unique.h>
#include <cppassist/string/regex.h>
#include <cppassist/string/conversion.h>
#include <cppassist/fs/RawFile.h>
#include <cppassist/fs/DescriptiveRawFile.h>


using namespace rendercore;


namespace
{


/**
*  @brief
*    Image format description
*/
struct ImageFormat
{
    bool     valid;      ///< Is the format valid?
    int      width;      ///< Width of the image
    int      height;     ///< Height of the image
    bool     compressed; ///< Is image compressed?
    Format   format;     ///< Format of the image
    DataType type;       ///< Type of the image
};

// Color formats and their names
static const std::map<std::string, Format> formatsBySuffix = {
    { "r",      Format::Red   },
    { "g",      Format::Green },
    { "b",      Format::Blue  },
    { "rg",     Format::RG    },
    { "rgb",    Format::RGB   },
    { "bgr",    Format::BGR   },
    { "rgba",   Format::RGBA  },
    { "bgra",   Format::BGRA  }
};

// Data types and their names
static const std::map<std::string, DataType> typesBySuffix = {
    { "ub",             DataType::Unsigned_Byte                      },
    { "b",              DataType::Byte                               },
    { "us",             DataType::Unsigned_Short                     },
    { "s",              DataType::Short                              },
    { "ui",             DataType::Unsigned_Int                       },
    { "i",              DataType::Int                                },
    { "f",              DataType::Float                              },
    { "rgtc1-r",        DataType::Compressed_Red_RGTC1,              },
    { "rgtc1-sr",       DataType::Compressed_Signed_Red_RGTC1        },
    { "rgtc2-rg",       DataType::Compressed_RG_RGTC2                },
    { "rgtc2-srg",      DataType::Compressed_Signed_RG_RGTC2         },
    { "bptc-rgba-unorm",DataType::Compressed_RGBA_BPTC_Unorm         },
    { "bptc-rgb-sf",    DataType::Compressed_RGB_BPTC_Signed_Float   },
    { "bptc-rgb-uf",    DataType::Compressed_RGB_BPTC_Unsigned_Float },
    { "dxt1-rgb",       DataType::Compressed_RGB_S3TC_DXT1           },
    { "dxt1-rgba",      DataType::Compressed_RGBA_S3TC_DXT1          },
    { "dxt3-rgba",      DataType::Compressed_RGBA_S3TC_DXT3          },
    { "dxt5-rgba",      DataType::Compressed_RGBA_S3TC_DXT5          }
};

// Regular expressions describing possible filename formats
static const std::string regex1 = "(^.*\\.(\\d+)\\.(\\d+)\\.(\\w+)\\.raw$)";
static const std::string regex2 = "(^.*\\.(\\d+)\\.(\\d+)\\.(\\w+)\\.(\\w+)\\.raw$)";

/**
*  @brief
*    Parse image format from filename
*
*  @param[in] filename
*    File name
*
*  @return
*    Image format
*/
static ImageFormat getFormatFromFilename(const std::string & filename)
{
    // Initialize image format
    ImageFormat format;
    format.valid      = false;
    format.width      = -1;
    format.height     = -1;
    format.compressed = false;
    format.format     = Format::Unknown;
    format.type       = DataType::Unknown;

    // Parse filename format
    std::vector<std::string> base_match;

    // Match again compressed filename format
    if (cppassist::string::matchesRegex(filename, regex1)) {
        format.compressed = true;
        base_match = cppassist::string::extract(filename, regex1);
    }

    // Match again non-compressed filename format
    else if (cppassist::string::matchesRegex(filename, regex2)) {
        base_match = cppassist::string::extract(filename, regex2);
    }

    // Invalid filename format
    else {
        return format;
    }

    // Get parsing result
    format.width  = cppassist::string::fromString<int>(base_match[1]);
    format.height = cppassist::string::fromString<int>(base_match[2]);
    if (!format.compressed) {
        auto it = formatsBySuffix.find(cppassist::string::toLower(base_match[3]));
        format.format = (it != formatsBySuffix.end()) ? it->second : Format::Unknown;
    }
    {
        auto it = typesBySuffix.find(cppassist::string::toLower(base_match[format.compressed ? 3 : 4]));
        format.type = (it != typesBySuffix.end()) ? it->second : DataType::Unknown;
    }

    // Check if format is valid
    format.valid = (format.width != -1 && format.height != -1 && format.type != DataType::Unknown && (format.compressed || format.format != Format::Unknown));

    // Return format
    return format;
}


}


namespace rendercore
{


ImageLoader::ImageLoader(Environment *)
{
}

ImageLoader::~ImageLoader()
{
}

std::unique_ptr<Image> ImageLoader::load(const std::string & filename) const
{
    // Check filename extension
    std::string ext = cppfs::FilePath(filename).extension();
    if (ext == ".glraw") {
        // Parse glraw file (RAW file with extended header)
        return loadGLRawImage(filename);
    } else if (ext == ".raw") {
        // Parse RAW file (get image format from filename)
        return loadRawImage(filename);
    } else {
        // Unsupported file
        return nullptr;
    }
}

std::unique_ptr<Image> ImageLoader::loadGLRawImage(const std::string & filename) const
{
    cppassist::DescriptiveRawFile rawFile;

    // Read file
    if (!rawFile.load(filename)) {
        return nullptr;
    }

    // Get image width and height
    const int width  = rawFile.intProperty("width");
    const int height = rawFile.intProperty("height");

    // Create image
    auto image = cppassist::make_unique<Image>();

    // Get image format
    if (rawFile.hasIntProperty("format")) { // Uncompressed
        // Get format and type
        auto format = static_cast<Format>  (rawFile.intProperty("format"));
        auto type   = static_cast<DataType>(rawFile.intProperty("type"));

        // Copy image data
        image->setData(width, height, format, type, rawFile.data(), rawFile.size());
    } else { // Compressed
        // Get compressed format
        auto compressedFormat = static_cast<DataType>(rawFile.intProperty("compressedFormat"));
        auto size = rawFile.intProperty("size");

        // Copy image data
        image->setData(width, height, Format::Unknown, compressedFormat, rawFile.data(), size);
    }

    // Return image
    return std::move(image);
}

std::unique_ptr<Image> ImageLoader::loadRawImage(const std::string & filename) const
{
    cppassist::RawFile rawFile;

    // Determine image format from filename
    auto format = getFormatFromFilename(filename);
    if (!format.valid) {
        // Invalid format
        return nullptr;
    }

    // Read file
    if (!rawFile.load(filename)) {
        return nullptr;
    }

    // Create image
    auto image = cppassist::make_unique<Image>();

    // Check image format
    if (!format.compressed) { // Uncompressed
        // Copy image data
        image->setData(format.width, format.height, format.format, format.type, rawFile.data(), rawFile.size());
    } else { // Compressed
        // Copy image data
        image->setData(format.width, format.height, Format::Unknown, format.type, rawFile.data(), rawFile.size());
    }

    // Return image
    return std::move(image);
}


} // namespace rendercore
