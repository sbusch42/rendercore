
#pragma once


#include <memory>

#include <globjects/Buffer.h>

#include <rendercore-opengl/Shape.h>
#include <rendercore-opengl/Drawable.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Quad shape
*/
class RENDERCORE_OPENGL_API Quad : public Shape
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
    Quad(float size = 2.0f, cppassist::Flags<ShapeOption> options = ShapeOption::None);

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
    Quad(float width, float height, cppassist::Flags<ShapeOption> options = ShapeOption::None);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Quad();

    // Virtual AbstractDrawable functions
    virtual void draw() const override;

protected:
    std::unique_ptr<Drawable>          m_drawable;  ///< Underlying drawable object
    std::unique_ptr<globjects::Buffer> m_vertices;  ///< Vertex buffer
    std::unique_ptr<globjects::Buffer> m_texCoords; ///< Texture coordinate buffer
};


} // namespace opengl
} // namespace rendercore
