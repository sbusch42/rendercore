
#pragma once


namespace rendercore
{
namespace opengl
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


} // namespace opengl
} // namespace rendercore
