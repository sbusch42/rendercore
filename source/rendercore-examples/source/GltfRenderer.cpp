
#include <rendercore-examples/GltfRenderer.h>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>

#include <rendercore/rendercore.h>

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
, m_angle(0.0f)
{
    // Initialize object transformation
    m_transform.setTranslation({ 0.0f, 0.0f, 0.0f });
    m_transform.setScale      ({ 1.0f, 1.0f, 1.0f });
    m_transform.setRotation   (glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

    // Create camera
    m_camera = cppassist::make_unique<Camera>();

    // Load GLTF asset
    GltfLoader loader;
    auto asset = loader.load(rendercore::dataPath() + "/rendercore/gltf/BoxAnimated/BoxAnimated.gltf");

    // Transfer data from GLTF
    GltfConverter converter;
    converter.convert(*asset.get());

    auto & textures = converter.textures();
    for (auto & texture : textures) {
        texture->setContainer(this);
        m_textures.push_back(std::move(texture));
    }

    auto & materials = converter.materials();
    for (auto & material : materials) {
        material->setContainer(this);
        m_materials.push_back(std::move(material));
    }

    auto & meshes = converter.meshes();
    for (auto & mesh : meshes) {
        mesh->setContainer(this);
        m_meshes.push_back(std::move(mesh));
    }

    // Create mesh renderer
    m_meshRenderer = cppassist::make_unique<MeshRenderer>(this);
}

GltfRenderer::~GltfRenderer()
{
}

void GltfRenderer::onUpdate()
{
    // Advance counter
    m_counter++;

    // Rotate model
    m_angle += m_timeDelta * 1.0f;
    m_transform.setRotation(glm::angleAxis(m_angle, glm::vec3(0.0f, 1.0f, 0.0f)));

    // Animation has been updated, redraw the scene (will also issue another update)
    scheduleRedraw();
}

void GltfRenderer::onRender()
{
    // Update viewport
    gl::glViewport(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);

    // Clear screen
    gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

    // Update camera
    m_camera->lookAt(glm::vec3(0.0f, 0.0, 9.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_camera->perspective(glm::radians(40.0f), glm::ivec2(m_viewport.z, m_viewport.w), 0.1f, 64.0f);

    // Render mesh
    if (m_meshes.size() > 0) {
        m_meshRenderer->render(*m_meshes[0].get(), m_transform, m_camera.get());
    }
}


} // namespace examples
} // namespace rendercore
