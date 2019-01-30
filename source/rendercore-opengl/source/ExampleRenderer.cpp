
#include <rendercore-opengl/ExampleRenderer.h>

#include <iostream>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/functions.h>

#include <rendercore/rendercore.h>

#include <rendercore-opengl/Box.h>
#include <rendercore-opengl/GlrawTextureLoader.h>
#include <rendercore-opengl/ShaderLoader.h>


namespace rendercore
{
namespace opengl
{


ExampleRenderer::ExampleRenderer(Environment * environment)
: Renderer(environment)
, m_counter(0)
{
}

ExampleRenderer::~ExampleRenderer()
{
}

void ExampleRenderer::onContextInit(AbstractContext *)
{
    GlrawTextureLoader textureLoader(environment());
    ShaderLoader       shaderLoader(environment());

    // [DEBUG]
    std::cout << "onContextInit()" << std::endl;

    // Create camera
    m_camera = cppassist::make_unique<Camera>();

    // Create geometry
    m_geometry = cppassist::make_unique<Box>(2.0f, ShapeOption::IncludeTexCoords);

    // Load texture
    auto * texture = textureLoader.load(rendercore::dataPath() + "/rendercore/textures/brickwall.glraw");
    m_texture.reset(texture);

    // Load shaders
    auto * vertShader = shaderLoader.load(rendercore::dataPath() + "/rendercore/shaders/geometry/geometry.vert");
    m_vertShader.reset(vertShader);
    auto * fragShader = shaderLoader.load(rendercore::dataPath() + "/rendercore/shaders/geometry/geometry.frag");
    m_fragShader.reset(fragShader);

    // Create program
    m_program = cppassist::make_unique<globjects::Program>();
    m_program->attach(m_vertShader.get());
    m_program->attach(m_fragShader.get());
}

void ExampleRenderer::onContextDeinit(AbstractContext *)
{
    // [DEBUG]
    std::cout << "onContextDeinit()" << std::endl;

    // Destroy OpenGL objects
    m_program.reset();
    m_vertShader.reset();
    m_fragShader.reset();
    m_texture.reset();
    m_geometry.reset();
    m_camera.reset();
}

void ExampleRenderer::onUpdate()
{
    // [DEBUG]
    std::cout << "onUpdate(" << m_counter << ")" << std::endl;

    // Advance counter
    m_counter++;
}

void ExampleRenderer::onRender()
{
    // [DEBUG]
    std::cout << "onRender()" << std::endl;

    // Update viewport
    gl::glViewport(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);

    // Update camera
    m_camera->lookAt(glm::vec3(0.0f, 0.0, 9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_camera->perspective(glm::radians(40.0f), glm::ivec2(m_viewport.z, m_viewport.w), 0.1f, 64.0f);

    // Update uniforms
    m_program->setUniform<glm::mat4>("modelViewProjectionMatrix",    m_camera->viewProjectionMatrix());
    m_program->setUniform<glm::mat4>("viewProjectionMatrix",         m_camera->viewProjectionMatrix());
    m_program->setUniform<glm::mat4>("viewProjectionInvertedMatrix", m_camera->viewProjectionInvertedMatrix());
    m_program->setUniform<glm::mat4>("viewMatrix",                   m_camera->viewMatrix());
    m_program->setUniform<glm::mat4>("viewInvertexMatrix",           m_camera->viewInvertedMatrix());
    m_program->setUniform<glm::mat4>("projectionMatrix",             m_camera->projectionMatrix());
    m_program->setUniform<glm::mat4>("projectionInvertedMatrix",     m_camera->projectionInvertedMatrix());
    m_program->setUniform<glm::mat3>("normalMatrix",                 m_camera->normalMatrix());
    m_program->setUniform<int>      ("tex0",                         0);

    // Bind texture
    m_texture->bindActive(0);

    // Bind program
    m_program->use();

    // Set rendering states
    gl::glEnable(gl::GL_DEPTH_TEST);

    // Render geometry
    m_geometry->draw();

    // Release program
    m_program->release();

    // Release program
    m_texture->unbindActive(0);
}


} // namespace opengl
} // namespace rendercore
