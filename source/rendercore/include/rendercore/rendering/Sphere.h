
#pragma once


#include <memory>

#include <globjects/Buffer.h>

#include <rendercore/rendering/Shape.h>
#include <rendercore/rendering/Drawable.h>
#include <rendercore/rendering/Icosahedron.h>


namespace rendercore
{


/**
*  @brief
*    Sphere drawable
*/
class RENDERCORE_API Sphere : public Shape
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] radius
    *    Sphere radius
    *  @param[in] options
    *    Shape options
    */
    Sphere(float radius = 1.0f, cppassist::Flags<ShapeOption> options = ShapeOption::None);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Sphere();

    // Virtual AbstractDrawable functions
    virtual void draw() const override;

protected:
    std::unique_ptr<Icosahedron>       m_icosahedron; ///< Refinable icosahedron
    std::unique_ptr<Drawable>          m_drawable;    ///< Underlying drawable object
    std::unique_ptr<globjects::Buffer> m_vertices;    ///< Vertex buffer
    std::unique_ptr<globjects::Buffer> m_texCoords;   ///< Texture coordinate buffer
    std::unique_ptr<globjects::Buffer> m_indices;     ///< Index buffer
};


} // namespace rendercore
