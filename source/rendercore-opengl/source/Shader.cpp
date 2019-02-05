
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


Shader::Shader(GpuObject * parent)
: GpuObject(parent)
, m_type(gl::GL_NONE)
{
}

Shader::~Shader()
{
}

const globjects::Shader * Shader::shader() const
{
    return m_shader.get();
}

globjects::Shader * Shader::shader()
{
    return m_shader.get();
}

gl::GLenum Shader::type() const
{
    return m_type;
}

void Shader::setType(gl::GLenum type)
{
    m_type = type;
}

void Shader::setCode(gl::GLenum type, const std::string & code)
{
    m_type = type;
    m_code = code;
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

void Shader::onContextInit(AbstractContext *)
{
    // Check if shader type and code is set
    if (m_type != gl::GL_NONE && !m_code.empty()) {
        // Create shader
        m_shader = cppassist::make_unique<globjects::Shader>(m_type);

        // Create shader source from string
        m_source = globjects::Shader::sourceFromString(m_code);

        // Set shader source
        m_shader->setSource(m_source.get());
    }
}

void Shader::onContextDeinit(AbstractContext *)
{
    // Release shader
    m_shader.reset();
}


} // namespace opengl
} // namespace rendercore
