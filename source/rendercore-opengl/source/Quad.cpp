
#include <rendercore-opengl/Quad.h>

#include <glm/glm.hpp>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/enum.h>


namespace rendercore
{
namespace opengl
{


Quad::Quad(GpuContainer * container, float size, bool texCoords)
: Quad(container, size, size, texCoords)
{
}

Quad::Quad(GpuContainer * container, float width, float height, bool)
: Mesh(container)
{
    // Quad geometry
    static const std::array<glm::vec2, 4> vertices { {
          glm::vec2(-0.5f, -0.5f)
        , glm::vec2( 0.5f, -0.5f)
        , glm::vec2(-0.5f,  0.5f)
        , glm::vec2( 0.5f,  0.5f)
    } };

    static const std::array<glm::vec2, 4> texcoords { {
          glm::vec2(0.0f, 0.0f)
        , glm::vec2(1.0f, 0.0f)
        , glm::vec2(0.0f, 1.0f)
        , glm::vec2(1.0f, 1.0f)
    } };

    // Create scaled vertices
    auto scaledVertices = vertices;
    for (auto & vertex : scaledVertices) {
        vertex *= glm::vec2(width, height);
    }

    // Create buffers
    auto * vertexBuffer   = createBuffer(scaledVertices);
    auto * texCoordBuffer = createBuffer(texcoords);

    // Create vertex attribute for positions
    auto * positionAttribute = addVertexAttribute(
        vertexBuffer,
        0,
        0,
        sizeof(glm::vec2),
        gl::GL_FLOAT,
        2,
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
    geometry->setMode(gl::GL_TRIANGLE_STRIP);
    geometry->setCount(vertices.size());
    geometry->bindAttribute(0, positionAttribute);
    geometry->bindAttribute(1, texCoordAttribute);
    addGeometry(std::move(geometry));
}

Quad::~Quad()
{
}


} // namespace opengl
} // namespace rendercore
