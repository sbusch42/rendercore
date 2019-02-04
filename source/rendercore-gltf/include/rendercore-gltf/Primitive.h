
#pragma once


#include <string>
#include <map>

#include <rendercore-gltf/rendercore-gltf_api.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Primitive
*/
class RENDERCORE_GLTF_API Primitive
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
    ~Primitive();

    /**
    *  @brief
    *    Get mode
    *
    *  @return
    *    Primitive mode
    */
    unsigned int mode() const;

    /**
    *  @brief
    *    Set mode
    *
    *  @param[in] mode
    *    Primitive mode
    */
    void setMode(unsigned int mode);

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
    *    Get indices accessor
    *
    *  @return
    *    Accessor index (-1 for none)
    */
    int indices() const;

    /**
    *  @brief
    *    Set indices accessor
    *
    *  @param[in] indices
    *    Accessor index (-1 for none)
    */
    void setIndices(int indices);

    /**
    *  @brief
    *    Get attributes
    *
    *  @return
    *    Map of attribute name -> accessor index
    */
    std::map<std::string, unsigned int> attributes() const;

    /**
    *  @brief
    *    Set attributes
    *
    *  @param[in] attributes
    *    Map of attribute name -> accessor index
    */
    void setAttributes(const std::map<std::string, unsigned int> & attributes);

protected:
    unsigned int                        m_mode;       ///< Primitive mode
    unsigned int                        m_material;   ///< Material index
    int                                 m_indices;    ///< Accessor index (-1 for none)
    std::map<std::string, unsigned int> m_attributes; ///< Map of attribute name -> accessor index
};


} // namespace gltf
} // namespace rendercore
