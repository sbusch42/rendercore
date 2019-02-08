
#include <rendercore-opengl/Sphere.h>

#include <glm/glm.hpp>

#include <cppassist/memory/make_unique.h>

#include <glbinding/gl/enum.h>


namespace rendercore
{
namespace opengl
{


Sphere::Sphere(GpuContainer * container, float radius, bool texCoords)
: Geometry(container)
{
    // Create icosahedron
    m_icosahedron = cppassist::make_unique<Icosahedron>();
    m_icosahedron->generateGeometry(5);

    // Create scaled vertices
    auto scaledVertices = m_icosahedron->vertices();
    for (auto & vertex : scaledVertices) {
        vertex *= radius;
    }

    // Create primitive
    auto prim = cppassist::make_unique<opengl::Primitive>();
    prim->setMode(gl::GL_TRIANGLES);
    prim->setNumElements(m_icosahedron->indices().size() * std::tuple_size<Icosahedron::Face>::value);

    // Create vertex buffer
    auto * vertexBuffer = createBuffer(scaledVertices);

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

    // Bind attribute
    prim->bindAttribute(0, positionAttribute);

    // Add texture coordinates?
    if (texCoords) {
        // Generate texture coordinates
        m_icosahedron->generateTextureCoordinates();

        // Create texture coordinate buffer
        auto * texCoordBuffer = createBuffer(m_icosahedron->texcoords());

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

        // Bind attribute
        prim->bindAttribute(1, texCoordAttribute);
    }

    // Create index buffer
    auto * indexBuffer = createBuffer(m_icosahedron->indices());
    prim->setIndexBuffer(indexBuffer, gl::GL_UNSIGNED_SHORT);

    // Add primitive to geometry
    addPrimitive(std::move(prim));
}

Sphere::~Sphere()
{
}


} // namespace opengl
} // namespace rendercore
