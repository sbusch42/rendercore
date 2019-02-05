
#include <rendercore-opengl/Program.h>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>
#include <glbinding/gl/enum.h>

#include <rendercore-opengl/Shader.h>


namespace rendercore
{
namespace opengl
{


Program::Program(GpuContainer * container)
: GpuObject(container)
{
}

Program::~Program()
{
}

void Program::attach(std::unique_ptr<Shader> && shader)
{
    // Attach shader
    attach(shader.get());

    // Transfer ownership of shader
    m_owned.push_back(std::move(shader));
}

void Program::attach(Shader * shader)
{
    // Check if shader is not empty
    if (shader) {
        // Add shader to program
        m_shaders.push_back(shader);

        // Flag program invalid
        setValid(false);
    }
}

globjects::Program * Program::program()
{
    // Check if program needs to be updated or restored
    if (!m_program || !valid()) {
        // Create program
        m_program = cppassist::make_unique<globjects::Program>();

        // Attach shaders
        for (auto * shader : m_shaders) {
            m_program->attach(shader->shader());
        }

        // Flag program valid
        setValid(true);
    }

    // Return program
    return m_program.get();
}

void Program::onDeinit()
{
    // Release program
    m_program.reset();
}


} // namespace opengl
} // namespace rendercore
