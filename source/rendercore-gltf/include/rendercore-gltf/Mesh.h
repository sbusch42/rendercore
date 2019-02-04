
#pragma once


#include <memory>
#include <vector>

#include <rendercore-gltf/Primitive.h>


namespace rendercore
{
namespace gltf
{


/**
*  @brief
*    Mesh
*/
class RENDERCORE_GLTF_API Mesh
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Mesh();

    /**
    *  @brief
    *    Destructor
    */
    ~Mesh();

    /**
    *  @brief
    *    Get primitives
    *
    *  @return
    *    List of primitives
    */
    std::vector<Primitive *> primitives() const;

    /**
    *  @brief
    *    Add primitive
    *
    *  @param[in] primitive
    *    Primitive (must NOT be nullptr)
    */
    void addPrimitive(std::unique_ptr<Primitive> && primitive);

protected:
    std::vector< std::unique_ptr<Primitive> > m_primitives;
};


} // namespace gltf
} // namespace rendercore
