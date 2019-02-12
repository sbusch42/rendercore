
#include <rendercore/ImageLoader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <cppfs/FilePath.h>

#include <cppassist/memory/make_unique.h>
#include <cppassist/fs/DescriptiveRawFile.h>


using namespace rendercore;


namespace rendercore
{


ImageLoader::ImageLoader()
{
}

ImageLoader::~ImageLoader()
{
}

std::unique_ptr<Image> ImageLoader::load(const std::string & filename) const
{
    // Check filename extension
    std::string ext = cppfs::FilePath(filename).extension();
    if (ext == ".png" || ext == ".jpg") {
        // Load image file
        return loadCommonImage(filename);
    } else if (ext == ".glraw") {
        // Load glraw file (RAW file with extended header)
        return loadGLRawImage(filename);
    } else {
        // Unsupported file
        return nullptr;
    }
}

std::unique_ptr<Image> ImageLoader::loadCommonImage(const std::string & filename) const
{
    // Create image
    auto image = cppassist::make_unique<Image>();

    // Load image
    int width    = 0;
    int height   = 0;
    int channels = 0;
    char * data = reinterpret_cast<char *>(stbi_load(filename.c_str(), &width, &height, &channels, 4));
    if (data) {
        // Set image data
        unsigned int format = 6408; // gl::GL_RGBA
        unsigned int type   = 5121; // gl::GL_UNSIGNED_BYTE
        image->setData(width, height, 1, format, type, width * height * 4, data);

        // Free image data
        stbi_image_free(data);
    }

    // Return image
    return std::move(image);
}

std::unique_ptr<Image> ImageLoader::loadGLRawImage(const std::string & filename) const
{
    cppassist::DescriptiveRawFile rawFile;

    // Read file
    if (!rawFile.load(filename)) {
        return nullptr;
    }

    // Get image width and height
    unsigned int width  = rawFile.intProperty("width");
    unsigned int height = rawFile.intProperty("height");
    unsigned int depth  = rawFile.hasIntProperty("depth") ? rawFile.intProperty("depth") : 1;

    // Create image
    auto image = cppassist::make_unique<Image>();

    // Get image format
    if (rawFile.hasIntProperty("format")) { // Uncompressed
        // Get format and type
        unsigned int format = (unsigned int)rawFile.intProperty("format");
        unsigned int type   = (unsigned int)rawFile.intProperty("type");

        // Copy image data
        image->setData(width, height, depth, format, type, rawFile.size(), rawFile.data());
    } else { // Compressed
        // Get compressed format
        unsigned int format = 0;
        unsigned int type   = (unsigned int)rawFile.intProperty("compressedFormat");
        unsigned int size   = (unsigned int)rawFile.intProperty("size");

        // Copy image data
        image->setData(width, height, depth, format, type, size, rawFile.data());
    }

    // Return image
    return std::move(image);
}


} // namespace rendercore
