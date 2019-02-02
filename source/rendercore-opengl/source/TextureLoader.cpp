
#include <rendercore-opengl/TextureLoader.h>

#include <map>

#include <cppfs/FilePath.h>

#include <cppassist/string/regex.h>
#include <cppassist/string/conversion.h>
#include <cppassist/fs/RawFile.h>
#include <cppassist/fs/DescriptiveRawFile.h>

#include <glbinding/gl/enum.h>

#include <globjects/Texture.h>


namespace
{


/**
*  @brief
*    Texture format description
*/
struct TextureFormat
{
    bool       valid;      ///< Is the format valid?
    int        width;      ///< Width of the Texture
    int        height;     ///< Height of the Texture
    bool       compressed; ///< Is texture compressed?
    gl::GLenum format;     ///< Format of the Texture
    gl::GLenum type;       ///< Type of the Texture
};

// Color formats and their names
static const std::map<std::string, gl::GLenum> formatsBySuffix = {
    { "r",      gl::GL_RED      },
    { "g",      gl::GL_GREEN    },
    { "b",      gl::GL_BLUE     },
    { "rg",     gl::GL_RG       },
    { "rgb",    gl::GL_RGB      },
    { "bgr",    gl::GL_BGR      },
    { "rgba",   gl::GL_RGBA     },
    { "bgra",   gl::GL_BGRA     }
};

// Data types and their names
static const std::map<std::string, gl::GLenum> typesBySuffix = {
    { "ub",             gl::GL_UNSIGNED_BYTE    },
    { "b",              gl::GL_BYTE             },
    { "us",             gl::GL_UNSIGNED_SHORT   },
    { "s",              gl::GL_SHORT            },
    { "ui",             gl::GL_UNSIGNED_INT     },
    { "i",              gl::GL_INT              },
    { "f",              gl::GL_FLOAT            },
    { "rgtc1-r",        gl::GL_COMPRESSED_RED_RGTC1,        },
    { "rgtc1-sr",       gl::GL_COMPRESSED_SIGNED_RED_RGTC1  },
    { "rgtc2-rg",       gl::GL_COMPRESSED_RG_RGTC2          },
    { "rgtc2-srg",      gl::GL_COMPRESSED_SIGNED_RG_RGTC2   },
    { "bptc-rgba-unorm",gl::GL_COMPRESSED_RGBA_BPTC_UNORM_ARB           },
    { "bptc-rgb-sf",    gl::GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB     },
    { "bptc-rgb-uf",    gl::GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB   },
    { "dxt1-rgb",       gl::GL_COMPRESSED_RGB_S3TC_DXT1_EXT   },
    { "dxt1-rgba",      gl::GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  },
    { "dxt3-rgba",      gl::GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  },
    { "dxt5-rgba",      gl::GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  }
};

// Regular expressions describing possible filename formats
static const std::string regex1 = "(^.*\\.(\\d+)\\.(\\d+)\\.(\\w+)\\.raw$)";
static const std::string regex2 = "(^.*\\.(\\d+)\\.(\\d+)\\.(\\w+)\\.(\\w+)\\.raw$)";

/**
*  @brief
*    Parse texture format from filename
*
*  @param[in] filename
*    Texture filename
*
*  @return
*    Texture format
*/
static TextureFormat getFormatFromFilename(const std::string & filename)
{
    // Initialize texture format
    TextureFormat format;
    format.valid      = false;
    format.width      = -1;
    format.height     = -1;
    format.compressed = false;
    format.format     = gl::GL_NONE;
    format.type       = gl::GL_NONE;

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
        format.format = (it != formatsBySuffix.end()) ? it->second : gl::GL_NONE;
    }
    {
        auto it = typesBySuffix.find(cppassist::string::toLower(base_match[format.compressed ? 3 : 4]));
        format.type = (it != typesBySuffix.end()) ? it->second : gl::GL_NONE;
    }

    // Check if format is valid
    format.valid = (format.width != -1 && format.height != -1 && format.type != gl::GL_NONE && (format.compressed || format.format != gl::GL_NONE));

    // Return format
    return format;
}


}


namespace rendercore
{
namespace opengl
{


TextureLoader::TextureLoader(Environment *)
{
}

TextureLoader::~TextureLoader()
{
}

std::unique_ptr<globjects::Texture> TextureLoader::load(const std::string & filename) const
{
    // Check filename extension
    std::string ext = cppfs::FilePath(filename).extension();
    if (ext == ".glraw") {
        // Parse glraw file (RAW file with extended header)
        return loadGLRawImage(filename);
    } else if (ext == ".raw") {
        // Parse RAW file (get texture format from filename)
        return loadRawImage(filename);
    } else {
        // Unsupported file
        return nullptr;
    }
}

std::unique_ptr<globjects::Texture> TextureLoader::loadGLRawImage(const std::string & filename) const
{
    cppassist::DescriptiveRawFile rawFile;

    // Read file
    if (!rawFile.load(filename)) {
        return nullptr;
    }

    // Get texture width and height
    const int w = rawFile.intProperty("width");
    const int h = rawFile.intProperty("height");

    // Create texture object
    auto texture = globjects::Texture::createDefault(gl::GL_TEXTURE_2D);

    // Get texture format
    if (rawFile.hasIntProperty("format")) { // Uncompressed
        // Get format and type
        auto format = static_cast<gl::GLenum>(rawFile.intProperty("format"));
        auto type = static_cast<gl::GLenum>(rawFile.intProperty("type"));

        // Create texture buffer
        texture->image2D(
            0,
            gl::GL_RGBA8,
            w,
            h,
            0,
            format,
            type,
            rawFile.data()
        );
    } else { // Compressed
        // Get compressed format
        auto compressedFormat = static_cast<gl::GLenum>(rawFile.intProperty("compressedFormat"));
        auto size = rawFile.intProperty("size");

        // Create texture buffer
        texture->compressedImage2D(
            0,
            compressedFormat,
            w,
            h,
            0,
            size,
            rawFile.data()
        );
    }

    // Return texture object
    return std::move(texture);
}

std::unique_ptr<globjects::Texture> TextureLoader::loadRawImage(const std::string & filename) const
{
    cppassist::RawFile rawFile;

    // Determine texture format from filename
    auto format = getFormatFromFilename(filename);
    if (!format.valid) {
        // Invalid format
        return nullptr;
    }

    // Read file
    if (!rawFile.load(filename)) {
        return nullptr;
    }

    // Create texture object
    auto texture = globjects::Texture::createDefault(gl::GL_TEXTURE_2D);

    // Check texture format
    if (!format.compressed) { // Uncompressed
        // Create texture buffer
        texture->image2D(
            0,
            gl::GL_RGBA8,
            format.width,
            format.height,
            0,
            format.format,
            format.type,
            rawFile.data()
        );
    } else { // Compressed
        // Create texture buffer
        texture->compressedImage2D(
            0,
            gl::GL_RGBA8,
            format.width,
            format.height,
            0,
            rawFile.size(),
            rawFile.data()
        );
    }

    // Return texture object
    return std::move(texture);
}


} // namespace opengl
} // namespace rendercore
