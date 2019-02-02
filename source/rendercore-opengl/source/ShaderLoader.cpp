
#include <rendercore-opengl/ShaderLoader.h>

#include <unordered_map>

#include <cppassist/memory/make_unique.h>

#include <cppfs/FilePath.h>

#include <glbinding/gl/enum.h>

#include <globjects/base/File.h>
#include <globjects/Shader.h>


namespace
{


// Mapping of file extension to GLenum type
const std::unordered_map<std::string, gl::GLenum> m_extensionToType = {
    {".vert", gl::GL_VERTEX_SHADER},
    {".tesc", gl::GL_TESS_CONTROL_SHADER},
    {".tese", gl::GL_TESS_EVALUATION_SHADER},
    {".geom", gl::GL_GEOMETRY_SHADER},
    {".frag", gl::GL_FRAGMENT_SHADER},
    {".comp", gl::GL_COMPUTE_SHADER}
};


}


namespace rendercore
{
namespace opengl
{


ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

std::unique_ptr<globjects::Shader> ShaderLoader::load(const std::string & filename) const
{
    // Get filename extension
    auto ext = cppfs::FilePath(filename).extension();

    // Get shader type from extension
    auto it = m_extensionToType.find(ext);

    // Load file
    globjects::File * file = new globjects::File(filename, false);
    if (it == m_extensionToType.end() || file->string().empty()) {
        // Error loading file
        delete file;
        return nullptr;
    }

    // Create shader
    // [TODO] Remove file memory leak
    return cppassist::make_unique<globjects::Shader>((*it).second, file);
}


} // namespace opengl
} // namespace rendercore
