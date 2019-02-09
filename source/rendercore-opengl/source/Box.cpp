
#include <rendercore-opengl/Box.h>

#include <glm/glm.hpp>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/enum.h>

#include <rendercore-opengl/enums.h>


namespace rendercore
{
namespace opengl
{


Box::Box(GpuContainer * container, float size, bool texCoords)
: Box(container, size, size, size, texCoords)
{
}

Box::Box(GpuContainer * container, float width, float height, float depth, bool)
: Mesh(container)
{
    // Box geometry
    static const std::array<glm::vec3, 36> vertices { {
          glm::vec3(-0.5f, -0.5f,  0.5f)
        , glm::vec3( 0.5f, -0.5f,  0.5f)
        , glm::vec3(-0.5f,  0.5f,  0.5f)

        , glm::vec3( 0.5f, -0.5f,  0.5f)
        , glm::vec3( 0.5f,  0.5f,  0.5f)
        , glm::vec3(-0.5f,  0.5f,  0.5f)

        , glm::vec3(-0.5f, -0.5f, -0.5f)
        , glm::vec3(-0.5f,  0.5f, -0.5f)
        , glm::vec3( 0.5f, -0.5f, -0.5f)

        , glm::vec3(-0.5f,  0.5f, -0.5f)
        , glm::vec3( 0.5f,  0.5f, -0.5f)
        , glm::vec3( 0.5f, -0.5f, -0.5f)

        , glm::vec3(-0.5f, -0.5f,  0.5f)
        , glm::vec3(-0.5f,  0.5f,  0.5f)
        , glm::vec3(-0.5f, -0.5f, -0.5f)

        , glm::vec3(-0.5f,  0.5f,  0.5f)
        , glm::vec3(-0.5f,  0.5f, -0.5f)
        , glm::vec3(-0.5f, -0.5f, -0.5f)

        , glm::vec3( 0.5f, -0.5f, -0.5f)
        , glm::vec3( 0.5f,  0.5f, -0.5f)
        , glm::vec3( 0.5f, -0.5f,  0.5f)

        , glm::vec3( 0.5f,  0.5f, -0.5f)
        , glm::vec3( 0.5f,  0.5f,  0.5f)
        , glm::vec3( 0.5f, -0.5f,  0.5f)

        , glm::vec3(-0.5f,  0.5f,  0.5f)
        , glm::vec3( 0.5f,  0.5f,  0.5f)
        , glm::vec3(-0.5f,  0.5f, -0.5f)

        , glm::vec3( 0.5f,  0.5f,  0.5f)
        , glm::vec3( 0.5f,  0.5f, -0.5f)
        , glm::vec3(-0.5f,  0.5f, -0.5f)

        , glm::vec3(-0.5f, -0.5f,  0.5f)
        , glm::vec3(-0.5f, -0.5f, -0.5f)
        , glm::vec3( 0.5f, -0.5f,  0.5f)

        , glm::vec3(-0.5f, -0.5f, -0.5f)
        , glm::vec3( 0.5f, -0.5f, -0.5f)
        , glm::vec3( 0.5f, -0.5f,  0.5f)
    } };

    static const std::array<glm::vec2, 36> texcoords { {
          glm::vec2(0.0f, 0.0f)
        , glm::vec2(1.0f, 0.0f)
        , glm::vec2(0.0f, 1.0f)

        , glm::vec2(1.0f, 0.0f)
        , glm::vec2(1.0f, 1.0f)
        , glm::vec2(0.0f, 1.0f)

        , glm::vec2(1.0f, 0.0f)
        , glm::vec2(1.0f, 1.0f)
        , glm::vec2(0.0f, 0.0f)

        , glm::vec2(1.0f, 1.0f)
        , glm::vec2(0.0f, 1.0f)
        , glm::vec2(0.0f, 0.0f)

        , glm::vec2(1.0f, 0.0f)
        , glm::vec2(1.0f, 1.0f)
        , glm::vec2(0.0f, 0.0f)

        , glm::vec2(1.0f, 1.0f)
        , glm::vec2(0.0f, 1.0f)
        , glm::vec2(0.0f, 0.0f)

        , glm::vec2(1.0f, 0.0f)
        , glm::vec2(1.0f, 1.0f)
        , glm::vec2(0.0f, 0.0f)

        , glm::vec2(1.0f, 1.0f)
        , glm::vec2(0.0f, 1.0f)
        , glm::vec2(0.0f, 0.0f)

        , glm::vec2(0.0f, 0.0f)
        , glm::vec2(1.0f, 0.0f)
        , glm::vec2(0.0f, 1.0f)

        , glm::vec2(1.0f, 0.0f)
        , glm::vec2(1.0f, 1.0f)
        , glm::vec2(0.0f, 1.0f)

        , glm::vec2(0.0f, 1.0f)
        , glm::vec2(0.0f, 0.0f)
        , glm::vec2(1.0f, 1.0f)

        , glm::vec2(0.0f, 0.0f)
        , glm::vec2(1.0f, 0.0f)
        , glm::vec2(1.0f, 1.0f)
    } };

    // Create scaled vertices
    auto scaledVertices = vertices;
    for (auto & vertex : scaledVertices) {
        vertex *= glm::vec3(width, height, depth);
    }

    // Create buffers
    auto * vertexBuffer   = createBuffer(scaledVertices);
    auto * texCoordBuffer = createBuffer(texcoords);

    // Create vertex attribute for positions
    auto * positionAttribute = addVertexAttribute(
        vertexBuffer,
        0,
        0,
        sizeof(glm::vec3),
        gl::GL_FLOAT,
        3,
        false
    );

    // Create vertex attribute for texture coordinates
    auto * texCoordAttribute = addVertexAttribute(
        texCoordBuffer,
        0,
        0,
        sizeof(glm::vec2),
        gl::GL_FLOAT,
        2,
        false
    );

    // Add geometry
    auto geometry = cppassist::make_unique<opengl::Geometry>();
    geometry->setMode(gl::GL_TRIANGLES);
    geometry->setCount(vertices.size());
    geometry->bindAttribute((unsigned int)AttributeIndex::Position,  positionAttribute);
    geometry->bindAttribute((unsigned int)AttributeIndex::TexCoord0, texCoordAttribute);
    addGeometry(std::move(geometry));
}

Box::~Box()
{
}


} // namespace opengl
} // namespace rendercore
