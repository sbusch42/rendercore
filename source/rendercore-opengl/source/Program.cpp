
#include <rendercore-opengl/Program.h>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>
#include <glbinding/gl/enum.h>


namespace rendercore
{
namespace opengl
{


Program::Program(GpuObject * parent)
: GpuObject(parent)
{
}

Program::~Program()
{
}

const globjects::Program * Program::program() const
{
    return m_program.get();
}

globjects::Program * Program::program()
{
    return m_program.get();
}

void Program::attach(std::unique_ptr<Shader> shader)
{
    // Check if shader is not empty
    if (shader) {
        // Make program the parent of the shader
        shader->setParent(this);

        // Add shader to program
        m_shaders.push_back(std::move(shader));
    }
}

void Program::onContextInit(AbstractContext *)
{
    // Create program
    m_program = cppassist::make_unique<globjects::Program>();

    // Attach shaders
    for (auto & shader : m_shaders) {
        m_program->attach(shader->shader());
    }
}

void Program::onContextDeinit(AbstractContext *)
{
    // Release program
    m_program.reset();
}


} // namespace opengl
} // namespace rendercore
