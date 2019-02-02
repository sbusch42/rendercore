
#include <rendercore-opengl/Triangle.h>

#include <glm/glm.hpp>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/enum.h>

#include <globjects/Buffer.h>


namespace rendercore
{
namespace opengl
{


Triangle::Triangle(float size, bool texCoords)
: Triangle(size, size, texCoords)
{
}

Triangle::Triangle(float width, float height, bool texCoords)
{
    // Triangle geometry
    static const std::array<glm::vec2, 3> vertices { {
          glm::vec2(-0.5f, -0.5f)
        , glm::vec2( 0.0f,  0.5f)
        , glm::vec2( 0.5f, -0.5f)
    } };

    static const std::array<glm::vec2, 4> texcoords { {
          glm::vec2(0.0f, 0.0f)
        , glm::vec2(0.5f, 1.0f)
        , glm::vec2(1.0f, 0.0f)
    } };

    // Create drawable
    setPrimitiveMode(gl::GL_TRIANGLES);
    setDrawMode(DrawMode::Arrays);
    setSize(3);

    // Create vertex buffer
    auto v = vertices;

    for(auto & vertex : v) {
        vertex *= glm::vec2(width, height);
    }

    m_vertices = cppassist::make_unique<globjects::Buffer>();
    m_vertices->setData(v, gl::GL_STATIC_DRAW);

    bindAttribute(0, 0);
    setBuffer(0, m_vertices.get());
    setAttributeBindingBuffer(0, 0, 0, sizeof(glm::vec2));
    setAttributeBindingFormat(0, 2, gl::GL_FLOAT, gl::GL_FALSE, 0);
    enableAttributeBinding(0);

    // Create texture coordinate buffer
    if (texCoords)
    {
        m_texCoords = cppassist::make_unique<globjects::Buffer>();
        m_texCoords->setData(texcoords, gl::GL_STATIC_DRAW);

        bindAttribute(1, 1);
        setBuffer(1, m_texCoords.get());
        setAttributeBindingBuffer(1, 1, 0, sizeof(glm::vec2));
        setAttributeBindingFormat(1, 2, gl::GL_FLOAT, gl::GL_FALSE, 0);
        enableAttributeBinding(1);
    }
}

Triangle::~Triangle()
{
}


} // namespace opengl
} // namespace rendercore
