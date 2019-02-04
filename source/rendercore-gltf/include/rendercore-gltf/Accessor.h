
#pragma once


#include <string>
#include <vector>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Accessor
*/
class RENDERCORE_GLTF_API Accessor
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Accessor();

    /**
    *  @brief
    *    Destructor
    */
    ~Accessor();

    /**
    *  @brief
    *    Get buffer view
    *
    *  @return
    *    Buffer view index
    */
    unsigned int bufferView() const;

    /**
    *  @brief
    *    Set buffer view
    *
    *  @param[in] bufferView
    *    Buffer view index
    */
    void setBufferView(unsigned int bufferView);

    /**
    *  @brief
    *    Get data type
    *
    *  @return
    *    Data type
    */
    const std::string & dataType() const;

    /**
    *  @brief
    *    Set data type
    *
    *  @param[in] dataType
    *    Data type
    */
    void setDataType(const std::string & dataType);

    /**
    *  @brief
    *    Get component type
    *
    *  @return
    *    Component type (OpenGL enum)
    */
    unsigned int componentType() const;

    /**
    *  @brief
    *    Set component type
    *
    *  @param[in] componentType
    *    Component type (OpenGL enum)
    */
    void setComponentType(unsigned int componentType);

    /**
    *  @brief
    *    Get offset into buffer view
    *
    *  @return
    *    Offset (in bytes)
    */
    unsigned int offset() const;

    /**
    *  @brief
    *    Set offset into buffer view
    *
    *  @param[in] offset
    *    Offset (in bytes)
    */
    void setOffset(unsigned int offset);

    /**
    *  @brief
    *    Get count
    *
    *  @return
    *    Number of elements
    */
    unsigned int count() const;

    /**
    *  @brief
    *    Set count
    *
    *  @param[in] count
    *    Number of elements
    */
    void setCount(unsigned int count);

    /**
    *  @brief
    *    Get minimum value
    *
    *  @return
    *    Minimum value
    */
    std::vector<float> minValue() const;

    /**
    *  @brief
    *    Set minimum value
    *
    *  @param[in] minValue
    *    Minimum value
    */
    void setMinValue(const std::vector<float> & minValue);

    /**
    *  @brief
    *    Get maximum value
    *
    *  @return
    *    Maximum value
    */
    std::vector<float> maxValue() const;

    /**
    *  @brief
    *    Set maximum value
    *
    *  @param[in] maxValue
    *    Maximum value
    */
    void setMaxValue(const std::vector<float> & maxValue);

protected:
    unsigned int       m_bufferView;    ///< Buffer view index
    std::string        m_dataType;      ///< Data type (e.g., "SCALAR", "VEC3", ...)
    unsigned int       m_componentType; ///< Component type (OpenGL enum)
    unsigned int       m_offset;        ///< Offset (in bytes)
    unsigned int       m_count;         ///< Number of elements
    std::vector<float> m_minValue;      ///< Minimum value
    std::vector<float> m_maxValue;      ///< Maximum value
};


} // namespace gltf
} // namespace rendercore
