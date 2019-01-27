
#pragma once


#include <memory>

#include <globjects/Buffer.h>

#include <rendercore/rendering/Shape.h>
#include <rendercore/rendering/Drawable.h>


namespace rendercore
{


/**
*  @brief
*    Triangle shape
*/
class RENDERCORE_API Triangle : public Shape
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] size
    *    Edge width and height
    *  @param[in] options
    *    Shape options
    */
    Triangle(float size = 2.0f, cppassist::Flags<ShapeOption> options = ShapeOption::None);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] width
    *    Edge width
    *  @param[in] height
    *    Edge height
    *  @param[in] options
    *    Shape options
    */
    Triangle(float width, float height, cppassist::Flags<ShapeOption> options = ShapeOption::None);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Triangle();

    // Virtual AbstractDrawable functions
    virtual void draw() const override;

protected:
    std::unique_ptr<Drawable>          m_drawable;  ///< Underlying drawable object
    std::unique_ptr<globjects::Buffer> m_vertices;  ///< Vertex buffer
    std::unique_ptr<globjects::Buffer> m_texCoords; ///< Texture coordinate buffer
};


} // namespace rendercore
