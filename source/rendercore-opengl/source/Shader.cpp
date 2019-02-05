
#include <rendercore-opengl/Shader.h>

#include <cppassist/memory/make_unique.h>

#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>

#include <glbinding/gl/gl.h>
#include <glbinding/gl/enum.h>


using namespace cppfs;


namespace rendercore
{
namespace opengl
{


Shader::Shader(GpuContainer * container)
: GpuObject(container)
, m_type(gl::GL_NONE)
{
}

Shader::~Shader()
{
}

gl::GLenum Shader::type() const
{
    // Return shader type
    return m_type;
}

void Shader::setType(gl::GLenum type)
{
    // Set shader type
    m_type = type;

    // Mark shader invalid
    setValid(false);
}

void Shader::setCode(gl::GLenum type, const std::string & code)
{
    // Set shader type and code
    m_type = type;
    m_code = code;

    // Mark shader invalid
    setValid(false);
}

void Shader::load(gl::GLenum type, const std::string & filename)
{
    std::string code = "";

    // Read file
    auto f = fs::open(filename);
    if (f.exists()) {
        code = f.readFile();
    }

    // Set shader code
    setCode(type, code);
}

globjects::Shader * Shader::shader()
{
    // Check if shader is empty
    if (m_type == gl::GL_NONE || m_code.empty()) {
        return nullptr;
    }

    // Check if shader needs to be updated or restored
    if (!m_shader.get() || !valid()) {
        // Create shader
        m_shader = cppassist::make_unique<globjects::Shader>(m_type);

        // Create shader source from string
        m_source = globjects::Shader::sourceFromString(m_code);

        // Set shader source
        m_shader->setSource(m_source.get());

        // Flag shader valid
        setValid(true);
    }

    // Return shader
    return m_shader.get();
}

void Shader::onDeinit()
{
    // Release shader
    m_shader.reset();
}


} // namespace opengl
} // namespace rendercore
