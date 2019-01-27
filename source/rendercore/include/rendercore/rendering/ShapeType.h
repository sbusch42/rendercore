
#pragma once


#include <map>

#include <cppexpose/reflection/Property.h>


namespace rendercore
{


/**
*  @brief
*    Type of basic shapes
*/
enum class ShapeType : int
{
    None,     ///< No shape
    Point,    ///< Single point
    Triangle, ///< 2D triangle
    Quad,     ///< 2D rectangle or quad
    Box,      ///< 3D box or cube
    Sphere    ///< 3D sphere or ellipsoid
};

/**
*  @brief
*    Options for basic shapes
*/
enum class ShapeOption : int
{
    None = 0,            ///< No option
    IncludeTexCoords = 1 ///< Include texture coordinates in geometry
};


} // namespace rendercore


namespace cppexpose
{


template <>
struct EnumDefaultStrings<rendercore::ShapeType>
{
    std::map<rendercore::ShapeType, std::string> operator()()
    {
        std::map<rendercore::ShapeType, std::string> values;
        values[rendercore::ShapeType::None]     = "None";
        values[rendercore::ShapeType::Point]    = "Point";
        values[rendercore::ShapeType::Quad]     = "Quad";
        values[rendercore::ShapeType::Triangle] = "Triangle";
        values[rendercore::ShapeType::Box]      = "Box";
        values[rendercore::ShapeType::Sphere]   = "Sphere";

        return values;
    }
};


} // namespace cppexpose
