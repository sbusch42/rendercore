
#include <rendercore-opengl/Box.h>

#include <glm/glm.hpp>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/enum.h>


namespace rendercore
{
namespace opengl
{


Box::Box(float size, bool texCoords)
: Box(size, size, size, texCoords)
{
}

Box::Box(float width, float height, float depth, bool texCoords)
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

    // Create drawable
    setPrimitiveMode(gl::GL_TRIANGLES);
    setDrawMode(DrawMode::Arrays);
    setSize(36);

    // Create vertex buffer
    auto v = vertices;

    for (auto & vertex : v) {
        vertex *= glm::vec3(width, height, depth);
    }

    m_vertices = cppassist::make_unique<globjects::Buffer>();
    m_vertices->setData(v, gl::GL_STATIC_DRAW);

    bindAttribute(0, 0);
    setBuffer(0, m_vertices.get());
    setAttributeBindingBuffer(0, 0, 0, sizeof(glm::vec3));
    setAttributeBindingFormat(0, 3, gl::GL_FLOAT, gl::GL_FALSE, 0);
    enableAttributeBinding(0);

    // Create texture coordinate buffer
    if (texCoords) {
        m_texCoords = cppassist::make_unique<globjects::Buffer>();
        m_texCoords->setData(texcoords, gl::GL_STATIC_DRAW);

        bindAttribute(1, 1);
        setBuffer(1, m_texCoords.get());
        setAttributeBindingBuffer(1, 1, 0, sizeof(glm::vec2));
        setAttributeBindingFormat(1, 2, gl::GL_FLOAT, gl::GL_FALSE, 0);
        enableAttributeBinding(1);
    }
}

Box::~Box()
{
}


} // namespace opengl
} // namespace rendercore
