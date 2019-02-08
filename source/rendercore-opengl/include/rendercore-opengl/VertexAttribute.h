
#pragma once


#include <glbinding/gl/types.h>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


class Buffer;


/**
*  @brief
*    Vertex attribute buffer
*/
class RENDERCORE_OPENGL_API VertexAttribute
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] buffer
    *    Buffer that is used (must NOT be null!)
    *  @param[in] baseOffset
    *    Offset into the buffer (in bytes)
    *  @param[in] relativeOffset
    *    Relative offset of this attribute data (in bytes)
    *  @param[in] stride
    *    Number of bytes between two adjacent elements in the buffer (in bytes)
    *  @param[in] type
    *    Data type (e.g., gl::GL_FLOAT)
    *  @param[in] components
    *    Number of components
    *  @param[in] normalize
    *    Shall the data be normalized?
    */
    VertexAttribute(Buffer * buffer
      , unsigned int baseOffset
      , unsigned int relativeOffset
      , int stride
      , gl::GLenum type
      , unsigned int components
      , bool normalize);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~VertexAttribute();

    /**
    *  @brief
    *    Get buffer
    *
    *  @return
    *    Buffer that is used (never null)
    */
    Buffer * buffer() const;

    /**
    *  @brief
    *    Get base offset
    *
    *  @return
    *    Offset into the buffer (in bytes)
    */
    unsigned int baseOffset() const;

    /**
    *  @brief
    *    Get relative offset
    *
    *  @return
    *    Relative offset of this attribute data (in bytes)
    */
    unsigned int relativeOffset() const;

    /**
    *  @brief
    *    Get stride
    *
    *  @return
    *    Number of bytes between two adjacent elements in the buffer (in bytes)
    */
    unsigned int stride() const;

    /**
    *  @brief
    *    Get data type
    *
    *  @return
    *    Data type (e.g., gl::GL_FLOAT)
    */
    gl::GLenum type() const;

    /**
    *  @brief
    *    Get number of components
    *
    *  @return
    *    Number of components
    */
    unsigned int components() const;

    /**
    *  @brief
    *    Get normalization
    *
    *  @return
    *    Shall the data be normalized?
    */
    bool normalize() const;

protected:
    Buffer       * m_buffer;         ///< Buffer that is used (must NOT be null!)
    unsigned int   m_baseOffset;     ///< Offset into the buffer (in bytes)
    unsigned int   m_relativeOffset; ///< Relative offset of this attribute data (in bytes)
    unsigned int   m_stride;         ///< Number of bytes between two adjacent elements in the buffer (in bytes)
    gl::GLenum     m_type;           ///< Data type (e.g., gl::GL_FLOAT)
    unsigned int   m_components;     ///< Number of components
    bool           m_normalize;      ///< Shall the data be normalized?
};


} // namespace opengl
} // namespace rendercore
