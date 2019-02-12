
#include <rendercore-examples/MeshExampleRenderer.h>

#include <iostream>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>

#include <rendercore/rendercore.h>

#include <rendercore-opengl/Sphere.h>


using namespace rendercore::opengl;


namespace rendercore
{
namespace examples
{


MeshExampleRenderer::MeshExampleRenderer(GpuContainer * container)
: Renderer(container)
, m_counter(0)
, m_angle(0.0f)
{
    // Initialize object transformation
    m_transform.setTranslation({ 0.0f, 0.0f, 0.0f });
    m_transform.setScale      ({ 1.0f, 1.0f, 1.0f });
    m_transform.setRotation   (glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

    // Create camera
    m_camera = cppassist::make_unique<Camera>();

    // Load texture
    m_texture = cppassist::make_unique<Texture>(this);
    //m_texture->load(rendercore::dataPath() + "/rendercore/textures/brickwall.glraw");
    m_texture->load(rendercore::dataPath() + "/rendercore/textures/elegant-blue-floral-texture.png");

    // Create material
    m_material = cppassist::make_unique<Material>(this);
    m_material->setTexture("baseColor", m_texture.get());
    m_material->setValue<float>("metallicFactor", 1.0);
    m_material->setValue<float>("roughnessFactor", 0.5);

    // Create mesh
    m_mesh = cppassist::make_unique<Sphere>(this, 2.0f, true);
    for (size_t i=0; i<m_mesh->geometries().size(); i++) {
        m_mesh->geometry(i)->setMaterial(m_material.get());
    }

    // Create mesh renderer
    m_meshRenderer = cppassist::make_unique<MeshRenderer>(this);
}

MeshExampleRenderer::~MeshExampleRenderer()
{
}

void MeshExampleRenderer::onInit()
{
    // [DEBUG]
    std::cout << "onInit()" << std::endl;
}

void MeshExampleRenderer::onDeinit()
{
    // [DEBUG]
    std::cout << "onDeinit()" << std::endl;
}

void MeshExampleRenderer::onUpdate()
{
    // [DEBUG]
    // std::cout << "onUpdate(" << m_counter << ")" << std::endl;

    // Advance counter
    m_counter++;

    // Rotate model
    m_angle += m_timeDelta * 1.0f;
    m_transform.setRotation(glm::angleAxis(m_angle, glm::vec3(0.0f, 1.0f, 0.0f)));

    // Animation has been updated, redraw the scene (will also issue another update)
    scheduleRedraw();
}

void MeshExampleRenderer::onRender()
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

    // Render mesh
    m_meshRenderer->render(*m_mesh.get(), m_transform, m_camera.get());
}


} // namespace examples
} // namespace rendercore
