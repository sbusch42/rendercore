
#pragma once


#include <rendercore/scene/SceneNodeComponent.h>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


class Mesh;


/**
*  @brief
*    Scene node component that displays a mesh
*/
class RENDERCORE_OPENGL_API MeshComponent : public rendercore::SceneNodeComponent
{
public:
    /**
    *  @brief
    *    Constructor
    */
    MeshComponent();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~MeshComponent();

    /**
    *  @brief
    *    Get mesh
    *
    *  @return
    *    Associated mesh (can be null)
    */
    const Mesh * mesh() const;

    /**
    *  @brief
    *    Get mesh
    *
    *  @return
    *    Associated mesh (can be null)
    */
    Mesh * mesh();

    /**
    *  @brief
    *    Set mesh
    *
    *  @param[in] mesh
    *    Associated mesh (can be null)
    */
    void setMesh(Mesh * mesh);

protected:
    Mesh * m_mesh; ///< Associated mesh (can be null)
};


} // namespace opengl
} // namespace rendercore
