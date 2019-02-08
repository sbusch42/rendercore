
#pragma once


#include <memory>
#include <unordered_map>

#include <glbinding/gl/types.h>

#include <globjects/VertexArray.h>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


class Buffer;
class VertexAttribute;


/**
*  @brief
*    Geometry that can be rendered
*/
class RENDERCORE_OPENGL_API Primitive
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Primitive();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Primitive();

    /**
    *  @brief
    *    Get primitive mode
    *
    *  @return
    *    Primitive mode (e.g., GL_TRIANGLES)
    */
    gl::GLenum mode() const;

    /**
    *  @brief
    *    Set primitive mode
    *
    *  @param[in] mode
    *    Primitive mode (e.g., GL_TRIANGLES)
    */
    void setMode(gl::GLenum mode);

    /**
    *  @brief
    *    Get index buffer
    *
    *  @return
    *    Index buffer (can be null)
    */
    Buffer * indexBuffer() const;

    /**
    *  @brief
    *    Get index buffer type
    *
    *  @return
    *    Data type of index buffer (e.g., GL_UNSIGNED_INT)
    */
    gl::GLenum indexBufferType() const;

    /**
    *  @brief
    *    Set index buffer
    *
    *  @param[in] buffer
    *    Index buffer (can be null)
    *  @param[in] type
    *    Data type of index buffer (e.g., GL_UNSIGNED_INT)
    */
    void setIndexBuffer(Buffer * buffer, gl::GLenum type);

    /**
    *  @brief
    *    Get number of elements
    *
    *  @return
    *    Number of elements to render
    */
    unsigned int numElements() const;

    /**
    *  @brief
    *    Set number of elements
    *
    *  @param[in] numElements
    *    Number of elements to render
    */
    void setNumElements(unsigned int numElements);

    /**
    *  @brief
    *    Get attribute bindings
    *
    *  @return
    *    List of attribute bindings
    */
    const std::unordered_map<size_t, const VertexAttribute *> & attributeBindings() const;

    /**
    *  @brief
    *    Get attribute binding for given attribute index
    *
    *  @param[in] index
    *    Attribute index
    *
    *  @return
    *    Attribute binding (can be null)
    */
    const VertexAttribute * attributeBinding(size_t index) const;

    /**
    *  @brief
    *    Create attribute binding
    *
    *  @param[in] index
    *    Attribute index
    *  @param[in] vertexAttribute
    *    Vertex attribute to bind
    */
    void bindAttribute(size_t index, const VertexAttribute * vertexAttribute);

    /**
    *  @brief
    *    Get material
    *
    *  @return
    *    Material index
    */
    unsigned int material() const;

    /**
    *  @brief
    *    Set material
    *
    *  @param[in] material
    *    Material index
    */
    void setMaterial(unsigned int material);

    /**
    *  @brief
    *    Draw geometry
    *
    *  @remarks
    *    On the first call, the VAO for this geometry will be created
    *    and prepared according to the configuration of this object.
    *
    *  @notes
    *    - Requires an active rendering context
    */
    void draw();

    /**
    *  @brief
    *    De-Initialize geometry
    *
    *  @remarks
    *    This function must be called when the rendering context has been lost.
    *    It invalidates the VAO being held in this object, so that is has to
    *    be reconstructed on the next call to draw().
    *
    *  @notes
    *    - Requires an active rendering context
    */
    void deinit();

protected:
    /**
    *  @brief
    *    Create VAO from data
    *
    *  @notes
    *    - Requires an active rendering context
    */
    void prepareVAO();

protected:
    // Geometry configuration
    gl::GLenum     m_mode;        ///< Primitive mode (e.g., GL_TRIANGLES)
    Buffer       * m_indexBuffer; ///< Index buffer (can be null)
    gl::GLenum     m_indexType;   ///< Data type of index buffer (e.g., GL_UNSIGNED_INT)
    unsigned int   m_numElements; ///< Number of elements to render
    unsigned int   m_material;    ///< Material index

    // Attributes
    std::unordered_map<size_t, const VertexAttribute *> m_attributes; ///< Vertex attribute bindings

    // OpenGL objects
    std::unique_ptr<globjects::VertexArray> m_vao; ///< Vertex array object
};


} // namespace opengl
} // namespace rendercore
