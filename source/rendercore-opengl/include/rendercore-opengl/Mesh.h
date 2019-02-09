
#pragma once


#include <memory>
#include <vector>
#include <array>
#include <unordered_map>

#include <rendercore/GpuContainer.h>
#include <rendercore/AbstractDrawable.h>

#include <rendercore-opengl/Buffer.h>
#include <rendercore-opengl/Geometry.h>
#include <rendercore-opengl/VertexAttribute.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Mesh that can be rendered
*/
class RENDERCORE_OPENGL_API Mesh : public rendercore::GpuContainer, public AbstractDrawable
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    Mesh(GpuContainer * container = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Mesh();

    /**
    *  @brief
    *    Get buffers
    *
    *  @return
    *    Associated buffers
    */
    const std::vector< Buffer * > & buffers() const;

    /**
    *  @brief
    *    Get buffer
    *
    *  @param[in] index
    *    Buffer index
    *
    *  @return
    *    Buffer (can be null)
    */
    const Buffer * buffer(size_t index) const;

    /**
    *  @brief
    *    Get buffer
    *
    *  @param[in] index
    *    Buffer index
    *
    *  @return
    *    Buffer (can be null)
    */
    Buffer * buffer(size_t index);

    /**
    *  @brief
    *    Set buffer
    *
    *  @param[in] buffer
    *    Buffer (must NOT be null!)
    */
    void addBuffer(Buffer * buffer);

    /**
    *  @brief
    *    Add buffer
    *
    *  @param[in] buffer
    *    Buffer (must NOT be null!)
    *
    *  @remarks
    *    Transfers ownership over the buffer to the geometry.
    */
    void addBuffer(std::unique_ptr<Buffer> && buffer);

    /**
    *  @brief
    *    Create buffer from data
    *
    *  @param[in] data
    *    Buffer data (can be null)
    *  @param[in] size
    *    Data size
    *
    *  @return
    *    Buffer (can be null)
    */
    Buffer * createBuffer(const void * data, unsigned int size);

    /**
    *  @brief
    *    Create buffer from typed vector
    *
    *  @tparam Type
    *    The element type
    *  @param[in] data
    *    Buffer data
    */
    template <typename Type>
    Buffer * createBuffer(const std::vector<Type> & data);

    /**
    *  @brief
    *    Create buffer from typed array
    *
    *  @tparam Type
    *    The element type
    *  @tparam Count
    *    The number of elements
    *  @param[in] data
    *    Buffer data
    */
    template <typename Type, std::size_t Count>
    Buffer * createBuffer(const std::array<Type, Count> & data);

    /**
    *  @brief
    *    Get vertex attributes
    *
    *  @return
    *    Vertex attributes
    */
    const std::vector< std::unique_ptr<VertexAttribute> > & vertexAttributes() const;

    /**
    *  @brief
    *    Add vertex attribute
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
    *
    *  @return
    *    Vertex attribute (never null)
    */
    VertexAttribute * addVertexAttribute(Buffer * buffer
      , unsigned int baseOffset
      , unsigned int relativeOffset
      , int stride
      , gl::GLenum type
      , unsigned int components
      , bool normalize);

    /**
    *  @brief
    *    Get geometries
    *
    *  @return
    *    Geometries
    */
    const std::vector< std::unique_ptr<Geometry> > & geometries() const;

    /**
    *  @brief
    *    Get geometry
    *
    *  @param[in] index
    *    Geometry index
    *
    *  @return
    *    Geometry at given index (can be null)
    */
    const Geometry * geometry(size_t index) const;

    /**
    *  @brief
    *    Add geometry
    *
    *  @param[in] geometry
    *    Geometry
    */
    void addGeometry(std::unique_ptr<Geometry> && geometry);

    // Virtual AbstractDrawable functions
    virtual void draw() const override;

protected:
    // Virtual GpuObject functions
    virtual void onDeinit() override;

protected:
    // Buffers
    std::vector< Buffer * >                m_buffers;    ///< Buffers associated with this geometry
    std::vector< std::unique_ptr<Buffer> > m_ownbuffers; ///< Buffers that are owned by the geometry

    // Vertex attributes
    std::vector< std::unique_ptr<VertexAttribute> > m_vertexAttributes; ///< List of vertex attributes

    // Geometries
    std::vector< std::unique_ptr<Geometry> > m_geometries; ///< List of geometries that are drawn
};


} // namespace opengl
} // namespace rendercore


#include <rendercore-opengl/Mesh.inl>
