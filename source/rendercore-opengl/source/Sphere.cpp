
#include <rendercore-opengl/Sphere.h>

#include <glm/glm.hpp>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/enum.h>


namespace rendercore
{
namespace opengl
{


Sphere::Sphere(float radius, bool texCoords)
{
    // Create icosahedron
    m_icosahedron = cppassist::make_unique<Icosahedron>();
    m_icosahedron->generateGeometry(5);

    // Create drawable
    setPrimitiveMode(gl::GL_TRIANGLES);
    setDrawMode(rendercore::opengl::DrawMode::ElementsIndexBuffer);
    setSize(m_icosahedron->indices().size() * std::tuple_size<Icosahedron::Face>::value);

    // Create vertex buffer
    auto vertices = m_icosahedron->vertices();

    for (auto & vertex : vertices) {
        vertex *= radius;
    }

    m_vertices = cppassist::make_unique<globjects::Buffer>();
    m_vertices->setData(vertices, gl::GL_STATIC_DRAW);

    bindAttribute(0, 0);
    setBuffer(0, m_vertices.get());
    setAttributeBindingBuffer(0, 0, 0, sizeof(glm::vec3));
    setAttributeBindingFormat(0, 3, gl::GL_FLOAT, gl::GL_FALSE, 0);
    enableAttributeBinding(0);

    // Create texture coordinate buffer
    if (texCoords) {
        m_icosahedron->generateTextureCoordinates();

        m_texCoords = cppassist::make_unique<globjects::Buffer>();
        m_texCoords->setData(m_icosahedron->texcoords(), gl::GL_STATIC_DRAW);

        bindAttribute(1, 1);
        setBuffer(1, m_texCoords.get());
        setAttributeBindingBuffer(1, 1, 0, sizeof(glm::vec2));
        setAttributeBindingFormat(1, 2, gl::GL_FLOAT, gl::GL_FALSE, 0);
        enableAttributeBinding(1);
    }

    // Create index buffer
    m_indices = cppassist::make_unique<globjects::Buffer>();
    m_indices->setData(m_icosahedron->indices(), gl::GL_STATIC_DRAW);

    setIndexBuffer(m_indices.get(), gl::GL_UNSIGNED_SHORT);
}

Sphere::~Sphere()
{
}


} // namespace opengl
} // namespace rendercore
