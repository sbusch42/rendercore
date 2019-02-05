
#pragma once


#include <memory>
#include <unordered_map>

#include <rendercore/GpuObject.h>

#include <rendercore-opengl/Buffer.h>
#include <rendercore-opengl/Primitive.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Geometry that can be rendered
*/
class RENDERCORE_OPENGL_API Geometry2 : public rendercore::GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] parent
    *    Parent object (can be null)
    */
    Geometry2(GpuObject * parent = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Geometry2();

    /**
    *  @brief
    *    Get buffers
    *
    *  @return
    *    Associated buffers
    */
    const std::unordered_map< size_t, std::unique_ptr<Buffer> > & buffers() const;

    /**
    *  @brief
    *    Get buffer
    *
    *  @param[in] index
    *    Buffer index
    *
    *  @return
    *    Buffer at given index (can be null)
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
    *    Buffer at given index (can be null)
    */
    Buffer * buffer(size_t index);

    /**
    *  @brief
    *    Set buffer
    *
    *  @param[in] index
    *    Buffer index
    *  @param[in] buffer
    *    Buffer
    */
    void setBuffer(size_t index, std::unique_ptr<Buffer> && buffer);

    /**
    *  @brief
    *    Get primitives
    *
    *  @return
    *    Primitives
    */
    const std::vector< std::unique_ptr<Primitive> > & primitives() const;

    /**
    *  @brief
    *    Get primitive
    *
    *  @param[in] index
    *    Primitive index
    *
    *  @return
    *    Primitive at given index (can be null)
    */
    const Primitive * primitive(size_t index) const;

    /**
    *  @brief
    *    Add primitive
    *
    *  @param[in] primitive
    *    Primitive
    */
   void add(std::unique_ptr<Primitive> && primitive);

protected:
    // Virtual GpuObject functions
    virtual void onContextInit(AbstractContext * context) override;
    virtual void onContextDeinit(AbstractContext * context) override;

protected:
    std::unordered_map< size_t, std::unique_ptr<Buffer> > m_buffers;    ///< Buffers associated with this geometry
    std::vector< std::unique_ptr<Primitive> >             m_primitives; ///< List of primitives that are drawn
};


} // namespace opengl
} // namespace rendercore
