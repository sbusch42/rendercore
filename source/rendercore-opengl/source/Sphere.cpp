
#include <rendercore-opengl/Sphere.h>

#include <glm/glm.hpp>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/enum.h>


namespace rendercore
{
namespace opengl
{


Sphere::Sphere(float radius, cppassist::Flags<ShapeOption> options)
: Shape(ShapeType::Sphere, options)
{
    // Create icosahedron
    m_icosahedron = cppassist::make_unique<Icosahedron>();
    m_icosahedron->generateGeometry(5);

    // Create drawable
    m_geometry = cppassist::make_unique<Geometry>();
    m_geometry->setPrimitiveMode(gl::GL_TRIANGLES);
    m_geometry->setDrawMode(rendercore::opengl::DrawMode::ElementsIndexBuffer);
    m_geometry->setSize(m_icosahedron->indices().size() * std::tuple_size<Icosahedron::Face>::value);

    // Create vertex buffer
    auto vertices = m_icosahedron->vertices();

    for (auto & vertex : vertices) {
        vertex *= radius;
    }

    m_vertices = cppassist::make_unique<globjects::Buffer>();
    m_vertices->setData(vertices, gl::GL_STATIC_DRAW);

    m_geometry->bindAttribute(0, 0);
    m_geometry->setBuffer(0, m_vertices.get());
    m_geometry->setAttributeBindingBuffer(0, 0, 0, sizeof(glm::vec3));
    m_geometry->setAttributeBindingFormat(0, 3, gl::GL_FLOAT, gl::GL_FALSE, 0);
    m_geometry->enableAttributeBinding(0);

    // Create texture coordinate buffer
    if (options & ShapeOption::IncludeTexCoords) {
        m_icosahedron->generateTextureCoordinates();

        m_texCoords = cppassist::make_unique<globjects::Buffer>();
        m_texCoords->setData(m_icosahedron->texcoords(), gl::GL_STATIC_DRAW);

        m_geometry->bindAttribute(1, 1);
        m_geometry->setBuffer(1, m_texCoords.get());
        m_geometry->setAttributeBindingBuffer(1, 1, 0, sizeof(glm::vec2));
        m_geometry->setAttributeBindingFormat(1, 2, gl::GL_FLOAT, gl::GL_FALSE, 0);
        m_geometry->enableAttributeBinding(1);
    }

    // Create index buffer
    m_indices = cppassist::make_unique<globjects::Buffer>();
    m_indices->setData(m_icosahedron->indices(), gl::GL_STATIC_DRAW);

    m_geometry->setIndexBuffer(m_indices.get(), gl::GL_UNSIGNED_SHORT);
}

Sphere::~Sphere()
{
}

void Sphere::draw() const
{
    m_geometry->draw();
}


} // namespace opengl
} // namespace rendercore
