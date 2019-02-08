
#pragma once


#include <memory>
#include <vector>
#include <array>

#include <globjects/Buffer.h>

#include <rendercore/GpuObject.h>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Buffer holding GPU data
*/
class RENDERCORE_OPENGL_API Buffer : public rendercore::GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    Buffer(GpuContainer * container = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Buffer();

    /**
    *  @brief
    *    Get data size
    *
    *  @return
    *    Data size (in bytes)
    */
    unsigned int size() const;

    /**
    *  @brief
    *    Get data
    *
    *  @return
    *    Buffer data (can be null)
    */
    const char * data() const;

    /**
    *  @brief
    *    Get data
    *
    *  @return
    *    Buffer data (can be null)
    */
    char * data();

    /**
    *  @brief
    *    Set data
    *
    *  @param[in] data
    *    Buffer data (can be null)
    *  @param[in] size
    *    Data size (in bytes)
    */
    void setData(const void * data, unsigned int size);

    /**
    *  @brief
    *    Set data from typed vector
    *
    *  @tparam Type
    *    The element type
    *  @param[in] data
    *    Buffer data
    */
    template <typename Type>
    void setData(const std::vector<Type> & data);

    /**
    *  @brief
    *    Set data from typed array
    *
    *  @tparam Type
    *    The element type
    *  @tparam Count
    *    The number of elements
    *  @param[in] data
    *    Buffer data
    */
    template <typename Type, std::size_t Count>
    void setData(const std::array<Type, Count> & data);

    /**
    *  @brief
    *    Allocate data
    *
    *  @param[in] size
    *    Data size (in bytes)
    */
    void allocate(unsigned int size);

    /**
    *  @brief
    *    Allocate data for a specific data type
    *
    *  @tparam Type
    *    The element type
    *  @param[in] numElements
    *    Number of elements
    */
    template <typename Type>
    void allocate(unsigned int numElements);

    /**
    *  @brief
    *    Get OpenGL buffer
    *
    *  @return
    *    OpenGL buffer (can be null)
    *
    *  @notes
    *    - Requires an active rendering context
    */
    globjects::Buffer * buffer();

protected:
    // Virtual GpuObject functions
    virtual void onDeinit() override;

    /**
    *  @brief
    *    Create buffer from data
    */
    void createFromData();

protected:
    std::unique_ptr<globjects::Buffer> m_buffer; ///< OpenGL buffer (can be null)
    std::vector<char>                  m_data;   ///< Buffer data
};


} // namespace opengl
} // namespace rendercore


#include <rendercore-opengl/Buffer.inl>
