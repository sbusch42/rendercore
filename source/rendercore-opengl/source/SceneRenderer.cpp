
#include <rendercore-opengl/SceneRenderer.h>

#include <glbinding/gl/gl.h>

#include <cppassist/memory/make_unique.h>

#include <rendercore/rendercore.h>
#include <rendercore/Camera.h>
#include <rendercore/Transform.h>
#include <rendercore/scene/Scene.h>
#include <rendercore/scene/SceneNode.h>

#include <rendercore-opengl/enums.h>
#include <rendercore-opengl/Mesh.h>
#include <rendercore-opengl/Material.h>
#include <rendercore-opengl/Shader.h>
#include <rendercore-opengl/Texture.h>
#include <rendercore-opengl/scene/MeshComponent.h>


namespace rendercore
{
namespace opengl
{


SceneRenderer::SceneRenderer(GpuContainer * container)
: GpuContainer(container)
{
    // Create program
    m_program = cppassist::make_unique<Program>(this);

    // Load vertex shader
    auto vertShader = cppassist::make_unique<Shader>(this);
    vertShader->load(gl::GL_VERTEX_SHADER, rendercore::dataPath() + "/rendercore/shaders/pbr/pbr.vert");
    m_program->attach(std::move(vertShader));

    // Load fragment shader
    auto fragShader = cppassist::make_unique<Shader>(this);
    fragShader->load(gl::GL_FRAGMENT_SHADER, rendercore::dataPath() + "/rendercore/shaders/pbr/pbr.frag");
    m_program->attach(std::move(fragShader));
}

SceneRenderer::~SceneRenderer()
{
}

void SceneRenderer::render(Scene & scene, const glm::mat4 & transform, Camera * camera)
{
    // Get root scene node
    SceneNode * node = scene.root();
    if (node) {
        // Render node and children
        render(*node, transform, camera);
    }
}

void SceneRenderer::render(SceneNode & node, const glm::mat4 & transform, Camera * camera)
{
    // Calculate transformation of this node
    glm::mat4 trans = transform * node.transform().transform();

    // Get mesh components
    auto meshComponents = node.components<MeshComponent>();
    for (auto * meshComponent : meshComponents) {
        // Get mesh
        auto * mesh = meshComponent->mesh();
        if (mesh) {
            // Render mesh
            render(*mesh, trans, camera);
        }
    }

    // Render child nodes
    for (auto & child : node.children()) {
        render(*child.get(), trans, camera);
    }
}

void SceneRenderer::render(Mesh & mesh, const glm::mat4 & transform, Camera * camera)
{
    // Set camera and model uniforms
    m_program->program()->setUniform<glm::mat4>("modelMatrix", transform);
    if (camera) {
        m_program->program()->setUniform<glm::mat4>("modelMatrix",                  transform);
        m_program->program()->setUniform<glm::mat4>("modelViewProjectionMatrix",    camera->viewProjectionMatrix() * transform);
        m_program->program()->setUniform<glm::mat4>("viewProjectionMatrix",         camera->viewProjectionMatrix());
        m_program->program()->setUniform<glm::mat4>("viewProjectionInvertedMatrix", camera->viewProjectionInvertedMatrix());
        m_program->program()->setUniform<glm::mat4>("viewMatrix",                   camera->viewMatrix());
        m_program->program()->setUniform<glm::mat4>("viewInvertexMatrix",           camera->viewInvertedMatrix());
        m_program->program()->setUniform<glm::mat4>("projectionMatrix",             camera->projectionMatrix());
        m_program->program()->setUniform<glm::mat4>("projectionInvertedMatrix",     camera->projectionInvertedMatrix());
        m_program->program()->setUniform<glm::mat3>("normalMatrix",                 camera->normalMatrix());
        m_program->program()->setUniform<glm::vec3>("eyePosition",                  camera->eyeFromViewMatrix());
        m_program->program()->setUniform<glm::vec3>("lightPosition",                camera->eyeFromViewMatrix());
    }

    // Bind program
    m_program->program()->use();

    // Render geometries
    auto & geometries = mesh.geometries();
    for (auto & geometry : geometries) {
        // Material options (defaults)
        glm::vec4   baseColorFactor(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec3   emissiveFactor (0.0f, 0.0f, 0.0f);
        float       metallicFactor  = 1.0f;
        float       roughnessFactor = 1.0f;
        std::string alphaMode       = "OPAQUE";
        float       alphaCutoff     = 0.5f;
        bool        doubleSided     = false;

        // Textures (defaults)
        Texture * baseColorTexture         = nullptr;
        Texture * metallicRoughnessTexture = nullptr;
        Texture * normalTexture            = nullptr;
        Texture * occlusionTexture         = nullptr;
        Texture * emissiveTexture          = nullptr;

        // Get material
        auto * material = geometry->material();
        if (material) {
            // Get material options
            if (material->hasAttribute("baseColorFactor")) { baseColorFactor = material->value<glm::vec4>  ("baseColorFactor"); }
            if (material->hasAttribute("metallicFactor"))  { metallicFactor  = material->value<float>      ("metallicFactor"); }
            if (material->hasAttribute("roughnessFactor")) { roughnessFactor = material->value<float>      ("roughnessFactor"); }
            if (material->hasAttribute("emissiveFactor"))  { emissiveFactor  = material->value<glm::vec3>  ("emissiveFactor"); }
            if (material->hasAttribute("alphaMode"))       { alphaMode       = material->value<std::string>("alphaMode"); }
            if (material->hasAttribute("alphaCutoff"))     { alphaCutoff     = material->value<float>      ("alphaCutoff"); }
            if (material->hasAttribute("doubleSided"))     { doubleSided     = material->value<bool>       ("doubleSided"); }

            // Get material textures
            baseColorTexture         = material->texture("baseColor");
            metallicRoughnessTexture = material->texture("metallicRoughness");
            normalTexture            = material->texture("normal");
            occlusionTexture         = material->texture("occlusion");
            emissiveTexture          = material->texture("emissive");
        }

        // Set material uniforms
        m_program->program()->setUniform<bool>     ("hasColors",         geometry->hasAttributeBinding((unsigned int)AttributeIndex::Color0));
        m_program->program()->setUniform<bool>     ("hasTexCoords",      geometry->hasAttributeBinding((unsigned int)AttributeIndex::TexCoord0));
        m_program->program()->setUniform<bool>     ("hasNormals",        geometry->hasAttributeBinding((unsigned int)AttributeIndex::Normal));
        m_program->program()->setUniform<bool>     ("hasTangents",       geometry->hasAttributeBinding((unsigned int)AttributeIndex::Tangent));
        m_program->program()->setUniform<glm::vec4>("baseColorFactor",   baseColorFactor);
        m_program->program()->setUniform<float>    ("metallicFactor",    metallicFactor);
        m_program->program()->setUniform<float>    ("roughnessFactor",   roughnessFactor);
        m_program->program()->setUniform<glm::vec3>("emissiveFactor",    emissiveFactor);
        if (alphaMode == "MASK") {
            m_program->program()->setUniform<float>("alphaCutoff",       alphaCutoff);
            m_program->program()->setUniform<float>("alphaBlendEnabled", 1.0f);
        } else if (alphaMode == "BLEND") {
            m_program->program()->setUniform<float>("alphaCutoff",       1.0f);
            m_program->program()->setUniform<float>("alphaBlendEnabled", 1.0f);
        } else {
            m_program->program()->setUniform<float>("alphaCutoff",       1.0f);
            m_program->program()->setUniform<float>("alphaBlendEnabled", 0.0f);
        }

        // Bind textures
        m_program->program()->setUniform<bool> ("hasBaseColorTexture", (baseColorTexture != nullptr));
        if (baseColorTexture) {
            baseColorTexture->texture()->bindActive(0);
            m_program->program()->setUniform<int>("baseColorTexture", 0);
        }

        m_program->program()->setUniform<bool> ("hasMetallicRoughnessTexture", (metallicRoughnessTexture != nullptr));
        if (metallicRoughnessTexture) {
            metallicRoughnessTexture->texture()->bindActive(1);
            m_program->program()->setUniform<int>("metallicRoughnessTexture", 1);
        }

        m_program->program()->setUniform<bool> ("hasNormalTexture", (normalTexture != nullptr));
        if (normalTexture) {
            normalTexture->texture()->bindActive(2);
            m_program->program()->setUniform<int>("normalTexture", 2);
        }

        m_program->program()->setUniform<bool> ("hasOcclusionTexture", (occlusionTexture != nullptr));
        if (occlusionTexture) {
            occlusionTexture->texture()->bindActive(3);
            m_program->program()->setUniform<int>("occlusionTexture", 3);
        }

        m_program->program()->setUniform<bool> ("hasEmissiveTexture", (emissiveTexture != nullptr));
        if (emissiveTexture) {
            emissiveTexture->texture()->bindActive(4);
            m_program->program()->setUniform<int>("emissiveTexture", 4);
        }

        // Set rendering states
        gl::glEnable(gl::GL_DEPTH_TEST);
        if (doubleSided) {
            gl::glDisable(gl::GL_CULL_FACE);
        } else {
            gl::glEnable(gl::GL_CULL_FACE);
            gl::glCullFace(gl::GL_BACK);
        }

        // Render geometry
        geometry->draw();

        // Release textures
        if (baseColorTexture)         baseColorTexture->texture()->unbindActive(0);
        if (metallicRoughnessTexture) metallicRoughnessTexture->texture()->unbindActive(1);
        if (normalTexture)            normalTexture->texture()->unbindActive(2);
        if (occlusionTexture)         occlusionTexture->texture()->unbindActive(3);
        if (emissiveTexture)          emissiveTexture->texture()->unbindActive(4);
    }

    // Release program
    m_program->program()->release();
}


} // namespace opengl
} // namespace rendercore
