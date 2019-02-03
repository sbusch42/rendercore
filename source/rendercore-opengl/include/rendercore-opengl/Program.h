
#pragma once


#include <memory>
#include <vector>

#include <globjects/Program.h>

#include <rendercore/GpuObject.h>

#include <rendercore-opengl/Shader.h>


namespace rendercore
{
namespace opengl
{


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
    *  @param[in] parent
    *    Parent object (can be null)
    */
    Program(GpuObject * parent);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Program();

    /**
    *  @brief
    *    Get OpenGL program
    *
    *  @return
    *    OpenGL program (can be null)
    */
    const globjects::Program * program() const;

    /**
    *  @brief
    *    Get OpenGL program
    *
    *  @return
    *    OpenGL program (can be null)
    */
    globjects::Program * program();

    /**
    *  @brief
    *    Attach shader to program
    *
    *  @param[in] shader
    *    Shader (must NOT be null!)
    */
    void attach(std::unique_ptr<Shader> shader);

protected:
    // Virtual GpuObject functions
    virtual void onContextInit(AbstractContext * context) override;
    virtual void onContextDeinit(AbstractContext * context) override;

protected:
    std::unique_ptr<globjects::Program>    m_program; ///< OpenGL program (can be null)
    std::vector< std::unique_ptr<Shader> > m_shaders; ///< Shaders attached to the program
};


} // namespace opengl
} // namespace rendercore
