
#pragma once


#include <memory>
#include <vector>

#include <globjects/Program.h>

#include <rendercore/GpuObject.h>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


class Shader;


/**
*  @brief
*    Program
*/
class RENDERCORE_OPENGL_API Program : public rendercore::GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    Program(GpuContainer * container = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Program();

    /**
    *  @brief
    *    Attach shader to program
    *
    *  @param[in] shader
    *    Shader (must NOT be null!)
    */
    void attach(Shader * shader);

    /**
    *  @brief
    *    Attach shader to program
    *
    *  @param[in] shader
    *    Shader (must NOT be null!)
    *
    *  @remarks
    *    Transfers ownership over the shader to the program.
    */
    void attach(std::unique_ptr<Shader> && shader);

    /**
    *  @brief
    *    Get OpenGL program
    *
    *  @return
    *    OpenGL program (can be null)
    *
    *  @notes
    *    - Requires an active rendering context
    */
    globjects::Program * program();

protected:
    // Virtual GpuObject functions
    virtual void onDeinit() override;

protected:
    std::unique_ptr<globjects::Program>    m_program; ///< OpenGL program (can be null)
    std::vector<Shader *>                  m_shaders; ///< Shaders attached to the program
    std::vector< std::unique_ptr<Shader> > m_owned;   ///< List of shaders owned by the program
};


} // namespace opengl
} // namespace rendercore
