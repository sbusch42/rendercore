
#pragma once


#include <map>
#include <memory>
#include <string>
#include <vector>

#include <rendercore/GpuObject.h>

#include <rendercore-opengl/MaterialAttribute.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Material
*/
class RENDERCORE_OPENGL_API Material : public rendercore::GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    Material(GpuContainer * container = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Material();

    /**
    *  @brief
    *    Get attributes
    *
    *  @return
    *    List of attribute names
    */
    std::vector<std::string> attributes() const;

    /**
    *  @brief
    *    Check if attribute exists
    *
    *  @param[in] name
    *    Attribute name
    *
    *  @return
    *    'true' if attribute exists, else 'false'
    */
    bool hasAttribute(const std::string & name) const;

    /**
    *  @brief
    *    Get attribute
    *
    *  @param[in] name
    *    Attribute name
    *
    *  @return
    *    Attribute (can be null)
    */
    const AbstractMaterialAttribute * attribute(const std::string & name) const;

    /**
    *  @brief
    *    Get typed attribute value
    *
    *  @tparam Type
    *    Data type
    *  @param[in] name
    *    Attribute name
    *
    *  @return
    *    Attribute value
    *
    *  @remarks
    *    If the attribute does not exist or does not have the specified type,
    *    a default value is returned.
    */
    template <typename Type>
    Type value(const std::string & name) const;

    /**
    *  @brief
    *    Set attribute value
    *
    *  @tparam Type
    *    Data type
    *  @param[in] name
    *    Attribute name
    *
    *  @remarks
    *    If the attribute exists but does not have the specified type,
    *    the value is not set. If the attribute does not exist, a new
    *    attribute of the specified type is created.
    */
    template <typename Type>
    void setValue(const std::string & name, const Type & value);

protected:
    // Virtual GpuObject functions
    virtual void onInit() override;
    virtual void onDeinit() override;

protected:
    std::map< std::string, std::unique_ptr<AbstractMaterialAttribute> > m_attributes; ///< Material attributes
};


} // namespace opengl
} // namespace rendercore


#include <rendercore-opengl/Material.inl>
