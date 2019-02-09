
#include <rendercore-opengl/MeshRenderer.h>

#include <glbinding/gl/gl.h>

#include <cppassist/memory/make_unique.h>

#include <rendercore/rendercore.h>
#include <rendercore/Camera.h>
#include <rendercore/Transform.h>

#include <rendercore-opengl/Mesh.h>
#include <rendercore-opengl/Material.h>
#include <rendercore-opengl/Shader.h>
#include <rendercore-opengl/Texture.h>


namespace rendercore
{
namespace opengl
{


MeshRenderer::MeshRenderer(GpuContainer * container)
: GpuContainer(container)
{
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

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render(Mesh & mesh, Transform & transform, Camera * camera)
{
    // Update uniforms
    m_program->program()->setUniform<glm::mat4>("modelMatrix", transform.transform());
    if (camera) {
        m_program->program()->setUniform<glm::mat4>("modelViewProjectionMatrix",    camera->viewProjectionMatrix() * transform.transform());
        m_program->program()->setUniform<glm::mat4>("viewProjectionMatrix",         camera->viewProjectionMatrix());
        m_program->program()->setUniform<glm::mat4>("viewProjectionInvertedMatrix", camera->viewProjectionInvertedMatrix());
        m_program->program()->setUniform<glm::mat4>("viewMatrix",                   camera->viewMatrix());
        m_program->program()->setUniform<glm::mat4>("viewInvertexMatrix",           camera->viewInvertedMatrix());
        m_program->program()->setUniform<glm::mat4>("projectionMatrix",             camera->projectionMatrix());
        m_program->program()->setUniform<glm::mat4>("projectionInvertedMatrix",     camera->projectionInvertedMatrix());
        m_program->program()->setUniform<glm::mat3>("normalMatrix",                 camera->normalMatrix());
    }

    // Set rendering states
    gl::glEnable(gl::GL_DEPTH_TEST);

    // Bind program
    m_program->program()->use();

    // Render geometries
    auto & geometries = mesh.geometries();
    for (auto & geometry : geometries) {
        // Material options (defaults)
        glm::vec4   baseColorFactor(1.0f, 1.0f, 1.0f, 1.0f);
        // glm::vec3   emissiveFactor (0.0f, 0.0f, 0.0f);
        // float       metallicFactor  = 1.0f;
        // float       roughnessFactor = 1.0f;
        // std::string alphaMode       = "OPAQUE";
        // float       alphaCutoff     = 0.5f;
        // bool        doubleSided     = false;

        // Textures (defaults)
        Texture * baseColorTexture         = nullptr;
        // Texture * metallicRoughnessTexture = nullptr;
        // Texture * normalTexture            = nullptr;
        // Texture * occlusionTexture         = nullptr;
        // Texture * emissiveTexture          = nullptr;

        // Get material
        auto * material = geometry->material();
        if (material) {
            // Get material options
            baseColorFactor = material->value<glm::vec4>  ("baseColorFactor");
            // emissiveFactor  = material->value<glm::vec3>  ("emissiveFactor");
            // metallicFactor  = material->value<float>      ("metallicFactor");
            // roughnessFactor = material->value<float>      ("roughnessFactor");
            // alphaMode       = material->value<std::string>("alphaMode");
            // alphaCutoff     = material->value<float>      ("alphaCutoff");
            // doubleSided     = material->value<bool>       ("doubleSided");

            // Get material textures
            baseColorTexture         = material->texture("baseColor");
            // metallicRoughnessTexture = material->texture("metallicRoughness");
            // normalTexture            = material->texture("normal");
            // occlusionTexture         = material->texture("occlusion");
            // emissiveTexture          = material->texture("emissive");
        }

        // Update uniforms
        m_program->program()->setUniform<bool>     ("baseColorTextureSet", (baseColorTexture != nullptr));
        m_program->program()->setUniform<glm::vec4>("baseColorFactor",     baseColorFactor);
        // [TODO]

        // Bind textures
        if (baseColorTexture) {
            baseColorTexture->texture()->bindActive(0);
            m_program->program()->setUniform<int>("baseColorTexture", 0);
        }

        // Render geometry
        geometry->draw();

        // Release textures
        if (baseColorTexture) {
            baseColorTexture->texture()->unbindActive(0);
        }
    }

    // Release program
    m_program->program()->release();
}


} // namespace opengl
} // namespace rendercore
