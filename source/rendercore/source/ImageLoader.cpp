
#include <rendercore/ImageLoader.h>

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
    if (ext == ".glraw") {
        // Parse glraw file (RAW file with extended header)
        return loadGLRawImage(filename);
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
