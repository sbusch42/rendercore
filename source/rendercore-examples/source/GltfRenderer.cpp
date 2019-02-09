
#include <rendercore-examples/GltfRenderer.h>

#include <iostream>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>

#include <rendercore/rendercore.h>

#include <rendercore-opengl/Shader.h>

#include <rendercore-gltf/GltfConverter.h>
#include <rendercore-gltf/GltfLoader.h>
#include <rendercore-gltf/Asset.h>


using namespace rendercore::opengl;
using namespace rendercore::gltf;


namespace rendercore
{
namespace examples
{


GltfRenderer::GltfRenderer(GpuContainer * container)
: Renderer(container)
, m_counter(0)
{
    // Initialize object transformation
    m_transform.setTranslation  ({ 0.0f, 0.0f, 0.0f });
    m_transform.setScale        ({ 1.0f, 1.0f, 1.0f });
    m_transform.setRotationAxis ({ 0.0f, 1.0f, 0.0f });
    m_transform.setRotationAngle(0.0f);

    // Create camera
    m_camera = cppassist::make_unique<Camera>();

    // Create program
    m_program = cppassist::make_unique<Program>(this);

    // Load vertex shader
    auto vertShader = cppassist::make_unique<Shader>(this);
    vertShader->load(gl::GL_VERTEX_SHADER, rendercore::dataPath() + "/rendercore/shaders/geometry/gltf.vert");
    m_program->attach(std::move(vertShader));

    // Load fragment shader
    auto fragShader = cppassist::make_unique<Shader>(this);
    fragShader->load(gl::GL_FRAGMENT_SHADER, rendercore::dataPath() + "/rendercore/shaders/geometry/gltf.frag");
    m_program->attach(std::move(fragShader));

    // Load GLTF asset
    GltfLoader loader;
    auto asset = loader.load(rendercore::dataPath() + "/rendercore/gltf/BoxAnimated/BoxAnimated.gltf");

    // Create mesh from GLTF
    GltfConverter converter;
    converter.convert(*asset.get(), rendercore::dataPath() + "/rendercore/gltf/BoxAnimated");
    m_geometry.reset(converter.geometry());
}

GltfRenderer::~GltfRenderer()
{
}

void GltfRenderer::onInit()
{
    // [DEBUG]
    std::cout << "onInit()" << std::endl;
}

void GltfRenderer::onDeinit()
{
    // [DEBUG]
    std::cout << "onDeinit()" << std::endl;
}

void GltfRenderer::onUpdate()
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

void GltfRenderer::onRender()
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

    // Bind program
    m_program->program()->use();

    // Set rendering states
    gl::glEnable(gl::GL_DEPTH_TEST);

    // Render geometry
    m_geometry->draw();

    // Release program
    m_program->program()->release();
}


} // namespace examples
} // namespace rendercore
