
#pragma once


#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Buffer view
*/
class RENDERCORE_GLTF_API BufferView
{
public:
    /**
    *  @brief
    *    Constructor
    */
    BufferView();

    /**
    *  @brief
    *    Destructor
    */
    ~BufferView();

    /**
    *  @brief
    *    Get buffer
    *
    *  @return
    *    Buffer index
    */
    unsigned int buffer() const;

    /**
    *  @brief
    *    Set buffer
    *
    *  @param[in] buffer
    *    Buffer index
    */
    void setBuffer(unsigned int buffer);

    /**
    *  @brief
    *    Get size
    *
    *  @return
    *    Size (in bytes)
    */
    unsigned int size() const;

    /**
    *  @brief
    *    Set size
    *
    *  @param[in] size
    *    Size (in bytes)
    */
    void setSize(unsigned int size);

    /**
    *  @brief
    *    Get offset into buffer
    *
    *  @return
    *    Offset (in bytes)
    */
    unsigned int offset() const;

    /**
    *  @brief
    *    Set offset into buffer
    *
    *  @param[in] offset
    *    Offset (in bytes)
    */
    void setOffset(unsigned int offset);

    /**
    *  @brief
    *    Get stride
    *
    *  @return
    *    Stride (in bytes)
    */
    unsigned int stride() const;

    /**
    *  @brief
    *    Set stride
    *
    *  @param[in] stride
    *    Stride (in bytes)
    */
    void setStride(unsigned int stride);

    /**
    *  @brief
    *    Get target
    *
    *  @return
    *    Target
    */
    unsigned int target() const;

    /**
    *  @brief
    *    Set target
    *
    *  @param[in] target
    *    Target
    */
    void setTarget(unsigned int target);

protected:
    unsigned int m_buffer; ///< Buffer index
    unsigned int m_size;   ///< Size (in bytes)
    unsigned int m_offset; ///< Offset (in bytes)
    unsigned int m_stride; ///< Stride (in bytes)
    unsigned int m_target; ///< Target
};


} // namespace gltf
} // namespace rendercore
