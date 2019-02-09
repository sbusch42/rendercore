
#pragma once


#include <rendercore/GpuContainer.h>

#include <rendercore-opengl/Program.h>


namespace rendercore
{


class Camera;
class Transform;


namespace opengl
{


class Mesh;


/**
*  @brief
*    Mesh renderer
*/
class RENDERCORE_OPENGL_API MeshRenderer : public GpuContainer
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (must NOT be null!)
    */
    MeshRenderer(GpuContainer * container);

    // Copying a renderer is not allowed
    MeshRenderer(const MeshRenderer &) = delete;

    // Copying a renderer is not allowed
    MeshRenderer & operator=(const MeshRenderer &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~MeshRenderer();

    /**
    *  @brief
    *    Render mesh
    *
    *  @param[in] mesh
    *    Mesh to render
    *  @param[in] transform
    *    Model transformation
    *  @param[in] camera
    *    Camera (can be null)
    */
    void render(Mesh & mesh, Transform & transform, Camera * camera);

protected:
    // GPU data
    std::unique_ptr<rendercore::opengl::Program>  m_program;  ///< Program used for rendering
};


} // namespace opengl
} // namespace rendercore
