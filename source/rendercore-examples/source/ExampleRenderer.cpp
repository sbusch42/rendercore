
#include <rendercore-examples/ExampleRenderer.h>

#include <iostream>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>

#include <rendercore/rendercore.h>

#include <rendercore-opengl/Box.h>


using namespace rendercore::opengl;


namespace rendercore
{
namespace examples
{


ExampleRenderer::ExampleRenderer()
: m_counter(0)
{
    // Initialize object transformation
    m_transform.setTranslation  ({ 0.0f, 0.0f, 0.0f });
    m_transform.setScale        ({ 1.0f, 1.0f, 1.0f });
    m_transform.setRotationAxis ({ 0.0f, 1.0f, 0.0f });
    m_transform.setRotationAngle(0.0f);

    // Create camera
    m_camera = cppassist::make_unique<Camera>();

    // Load texture
    m_texture = cppassist::make_unique<Texture>(this);
    m_texture->load(rendercore::dataPath() + "/rendercore/textures/brickwall.glraw");

    // Create program
    m_program = cppassist::make_unique<Program>(this);

    // Load vertex shader
    auto vertShader = cppassist::make_unique<Shader>(this);
    vertShader->load(gl::GL_VERTEX_SHADER, rendercore::dataPath() + "/rendercore/shaders/geometry/geometry.vert");
    m_program->attach(std::move(vertShader));

    // Load fragment shader
    auto fragShader = cppassist::make_unique<Shader>(this);
    fragShader->load(gl::GL_FRAGMENT_SHADER, rendercore::dataPath() + "/rendercore/shaders/geometry/geometry.frag");
    m_program->attach(std::move(fragShader));
}

ExampleRenderer::~ExampleRenderer()
{
}

void ExampleRenderer::onContextInit(AbstractContext *)
{
    // [DEBUG]
    std::cout << "onContextInit()" << std::endl;

    // Create geometry
    m_geometry = cppassist::make_unique<Box>(2.0f, true);
}

void ExampleRenderer::onContextDeinit(AbstractContext *)
{
    // [DEBUG]
    std::cout << "onContextDeinit()" << std::endl;

    // Destroy OpenGL objects
    m_geometry.reset();
}

void ExampleRenderer::onUpdate()
{
    // [DEBUG]
    // std::cout << "onUpdate(" << m_counter << ")" << std::endl;

    // Advance counter
    m_counter++;

    // Rotate model
    m_transform.setRotationAngle(m_transform.rotationAngle() + m_timeDelta * 1.0f);

    // Animation has been updated, redraw the scene (will also issue another update)
    scheduleRedraw();
}

void ExampleRenderer::onRender()
{
    // [DEBUG]
    // std::cout << "onRender()" << std::endl;

    // Update viewport
    gl::glViewport(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);

    // Clear screen
    gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

    // Update camera
    m_camera->lookAt(glm::vec3(0.0f, 0.0, 9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_camera->perspective(glm::radians(40.0f), glm::ivec2(m_viewport.z, m_viewport.w), 0.1f, 64.0f);

    // Update uniforms
    m_program->program()->setUniform<glm::mat4>("modelMatrix",                  m_transform.transform());
    m_program->program()->setUniform<glm::mat4>("modelViewProjectionMatrix",    m_camera->viewProjectionMatrix() * m_transform.transform());
    m_program->program()->setUniform<glm::mat4>("viewProjectionMatrix",         m_camera->viewProjectionMatrix());
    m_program->program()->setUniform<glm::mat4>("viewProjectionInvertedMatrix", m_camera->viewProjectionInvertedMatrix());
    m_program->program()->setUniform<glm::mat4>("viewMatrix",                   m_camera->viewMatrix());
    m_program->program()->setUniform<glm::mat4>("viewInvertexMatrix",           m_camera->viewInvertedMatrix());
    m_program->program()->setUniform<glm::mat4>("projectionMatrix",             m_camera->projectionMatrix());
    m_program->program()->setUniform<glm::mat4>("projectionInvertedMatrix",     m_camera->projectionInvertedMatrix());
    m_program->program()->setUniform<glm::mat3>("normalMatrix",                 m_camera->normalMatrix());
    m_program->program()->setUniform<int>      ("tex0",                         0);

    // Bind texture
    m_texture->texture()->bindActive(0);

    // Bind program
    m_program->program()->use();

    // Set rendering states
    gl::glEnable(gl::GL_DEPTH_TEST);

    // Render geometry
    m_geometry->draw();

    // Release program
    m_program->program()->release();

    // Release program
    m_texture->texture()->unbindActive(0);
}


} // namespace examples
} // namespace rendercore
