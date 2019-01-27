
#include <rendercore-opengl/Shape.h>


namespace rendercore
{
namespace opengl
{


Shape::Shape(ShapeType shapeType, cppassist::Flags<ShapeOption> options)
: m_type(shapeType)
, m_options(options)
{
}

Shape::~Shape()
{
}

ShapeType Shape::type() const
{
    return m_type;
}

cppassist::Flags<ShapeOption> Shape::options() const
{
    return m_options;
}

void Shape::draw() const
{
}

Shape::Shape(cppassist::Flags<ShapeOption> options)
: Shape(ShapeType::None, options)
{
}


} // namespace opengl
} // namespace rendercore
