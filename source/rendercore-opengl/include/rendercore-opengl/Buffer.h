
#pragma once


#include <memory>

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
    *    Data size
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
    *    Allocate data
    *
    *  @param[in] sue
    *    Data size
    */
    void allocate(unsigned int size);

    /**
    *  @brief
    *    Set data
    *
    *  @param[in] data
    *    Buffer data (can be null)
    *  @param[in] size
    *    Data size
    */
    void setData(char * data, unsigned int size);

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
