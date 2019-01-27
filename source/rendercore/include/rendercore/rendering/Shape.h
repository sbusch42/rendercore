
#pragma once


#include <map>

#include <cppexpose/reflection/Property.h>

#include <rendercore/rendering/AbstractDrawable.h>
#include <rendercore/rendering/ShapeType.h>

#include <cppassist/flags/Flags.h> // Must be included last


namespace rendercore
{


/**
*  @brief
*    Base class for basic shapes (quads, boxes, etc.)
*/
class RENDERCORE_API Shape : public AbstractDrawable
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] options
    *    Shape options
    */
    Shape(cppassist::Flags<ShapeOption> options);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Shape();

    /**
    *  @brief
    *    Get shape type
    *
    *  @return
    *    Type of the shape
    */
    ShapeType type() const;

    /**
    *  @brief
    *    Get shape options
    *
    *  @return
    *    Shape options
    */
    cppassist::Flags<ShapeOption> options() const;

    // Virtual AbstractDrawable functions
    virtual void draw() const override;

protected:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] type
    *    Type of the shape
    *  @param[in] options
    *    Shape options
    */
    Shape(ShapeType shapeType, cppassist::Flags<ShapeOption> options);

protected:
    ShapeType                     m_type;    ///< Type of the shape
    cppassist::Flags<ShapeOption> m_options; ///< Shape options
};


} // namespace rendercore
