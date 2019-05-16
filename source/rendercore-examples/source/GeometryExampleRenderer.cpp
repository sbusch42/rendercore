
#include <rendercore-examples/GeometryExampleRenderer.h>

#include <iostream>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/gl.h>

#include <rendercore/rendercore.h>

#include <rendercore-opengl/Geometry.h>
#include <rendercore-opengl/Shader.h>


using namespace rendercore::opengl;


namespace rendercore
{
namespace examples
{


GeometryExampleRenderer::GeometryExampleRenderer(GpuContainer * container)
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
    m_texture->load(rendercore::dataPath() + "/rendercore/textures/brickwall.glraw");

    // Create program
    m_program = cppassist::make_unique<Program>(this);

    // Load vertex shader
    auto vertShader = cppassist::make_unique<Shader>(this);
    vertShader->load(gl::GL_VERTEX_SHADER, rendercore::dataPath() + "/rendercore/shaders/geometry/basic.vert");
    m_program->attach(std::move(vertShader));

    // Load fragment shader
    auto fragShader = cppassist::make_unique<Shader>(this);
    fragShader->load(gl::GL_FRAGMENT_SHADER, rendercore::dataPath() + "/rendercore/shaders/geometry/basic.frag");
    m_program->attach(std::move(fragShader));

    // Create geometry
    createPoints();
}

GeometryExampleRenderer::~GeometryExampleRenderer()
{
}

void GeometryExampleRenderer::createPoints()
{
    // Positions
    static const std::array<glm::vec3, 8> positions { {
          glm::vec3(-0.5f, -0.5f, -0.5f)
        , glm::vec3( 0.5f, -0.5f, -0.5f)
        , glm::vec3( 0.5f, -0.5f,  0.5f)
        , glm::vec3(-0.5f, -0.5f,  0.5f)
        , glm::vec3(-0.5f,  0.5f, -0.5f)
        , glm::vec3( 0.5f,  0.5f, -0.5f)
        , glm::vec3( 0.5f,  0.5f,  0.5f)
        , glm::vec3(-0.5f,  0.5f,  0.5f)
    } };

    // Colors
    static const std::array<glm::vec3, 8> colors { {
          glm::vec3(0.0f, 0.0f, 0.0f)
        , glm::vec3(1.0f, 0.0f, 0.0f)
        , glm::vec3(1.0f, 0.0f, 1.0f)
        , glm::vec3(0.0f, 0.0f, 1.0f)
        , glm::vec3(0.0f, 1.0f, 0.0f)
        , glm::vec3(1.0f, 1.0f, 0.0f)
        , glm::vec3(1.0f, 1.0f, 1.0f)
        , glm::vec3(0.0f, 1.0f, 1.0f)
    } };

    // Indices
    static const std::array<unsigned int, 4> indices { {
        2, 3, 4, 5
    } };

    // Create geometry
    m_geometry = cppassist::make_unique<Mesh>(this);

    // Create buffers
    auto * positionBuffer = m_geometry->createBuffer(positions);
    auto * colorBuffer = m_geometry->createBuffer(colors);

    // Create vertex attribute for positions
    auto * positionAttribute = m_geometry->addVertexAttribute(
        positionBuffer,
        0,
        0,
        sizeof(glm::vec3),
        gl::GL_FLOAT,
        3,
        false
    );

    // Create vertex attribute for colors
    auto * colorAttribute  = m_geometry->addVertexAttribute(
        colorBuffer,
        0,
        0,
        sizeof(glm::vec3),
        gl::GL_FLOAT,
        3,
        false
    );

    // Create index buffer
    auto * indexBuffer = m_geometry->createBuffer(indices);

    // Add geometry
    auto points = cppassist::make_unique<opengl::Geometry>();
    points->setMode(gl::GL_POINTS);
    points->setIndexBuffer(indexBuffer, gl::GL_UNSIGNED_INT);
    points->setCount(indices.size());
    points->setMaterial(0);
    points->bindAttribute(0, positionAttribute);
    points->bindAttribute(1, colorAttribute);
    m_geometry->addGeometry(std::move(points));
}

void GeometryExampleRenderer::createPointsInterleaved()
{
    // Vertices (positions and colors)
    static const std::array<glm::vec3, 16> vertices { {
          // Positions                    // Colors
          glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)
        , glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)
        , glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 1.0f)
        , glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f)
        , glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)
        , glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f)
        , glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f)
        , glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 1.0f)
    } };

    // Indices
    static const std::array<unsigned int, 8> indices { {
        0, 1, 2, 3, 4, 5, 6, 7
    } };

    // Create geometry
    m_geometry = cppassist::make_unique<Mesh>(this);

    // Create vertex buffer
    auto * vertexBuffer = m_geometry->createBuffer(vertices);

    // Create vertex attribute for positions
    auto * positionAttribute  = m_geometry->addVertexAttribute(
        vertexBuffer,
        0,
        0,
        sizeof(glm::vec3) * 2,
        gl::GL_FLOAT,
        3,
        false
    );

    // Create vertex attribute for colors
    auto * colorAttribute  = m_geometry->addVertexAttribute(
        vertexBuffer,
        0,
        sizeof(glm::vec3),
        sizeof(glm::vec3) * 2,
        gl::GL_FLOAT,
        3,
        false
    );

    // Create index buffer
    auto * indexBuffer = m_geometry->createBuffer(indices);

    // Add geometry
    auto points = cppassist::make_unique<opengl::Geometry>();
    points->setMode(gl::GL_POINTS);
    points->setIndexBuffer(indexBuffer, gl::GL_UNSIGNED_INT);
    points->setCount(indices.size());
    points->setMaterial(0);
    points->bindAttribute(0, positionAttribute);
    points->bindAttribute(1, colorAttribute);
    m_geometry->addGeometry(std::move(points));
}

void GeometryExampleRenderer::onInit()
{
    // [DEBUG]
    std::cout << "onInit()" << std::endl;
}

void GeometryExampleRenderer::onDeinit()
{
    // [DEBUG]
    std::cout << "onDeinit()" << std::endl;
}

void GeometryExampleRenderer::onUpdate()
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

void GeometryExampleRenderer::onRender()
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

    // Release texture
    m_texture->texture()->unbindActive(0);
}


} // namespace examples
} // namespace rendercore
