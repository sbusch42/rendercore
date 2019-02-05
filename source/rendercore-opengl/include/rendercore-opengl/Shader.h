
#pragma once


#include <memory>

#include <globjects/Shader.h>
#include <globjects/base/StaticStringSource.h>

#include <rendercore/GpuObject.h>

#include <rendercore-opengl/rendercore-opengl_api.h>


namespace rendercore
{
namespace opengl
{


/**
*  @brief
*    Shader
*/
class RENDERCORE_OPENGL_API Shader : public rendercore::GpuObject
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] container
    *    GPU container (can be null)
    */
    Shader(GpuContainer * container = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Shader();

    /**
    *  @brief
    *    Get shader type
    *
    *  @return
    *    Shader type
    */
    gl::GLenum type() const;

    /**
    *  @brief
    *    Set shader type
    *
    *  @param[in] type
    *    Shader type
    */
    void setType(gl::GLenum type);

    /**
    *  @brief
    *    Set shader code
    *
    *  @param[in] type
    *    Shader type
    *  @param[in] code
    *    Shader code
    *
    *  @remarks
    *    The shader code will be compiled to a shader program.
    *    It will also be used to restore the shader when needed
    *    (e.g., after a context switch).
    */
    void setCode(gl::GLenum type, const std::string & code);

    /**
    *  @brief
    *    Load shader from file
    *
    *  @param[in] type
    *    Shader type
    *  @param[in] filename
    *    Path to shader file
    *
    *  @remarks
    *    This function will load the given file and set it as
    *    the source for this shader program (see setCode).
    */
    void load(gl::GLenum type, const std::string & filename);

    /**
    *  @brief
    *    Get OpenGL shader
    *
    *  @return
    *    OpenGL shader (can be null)
    *
    *  @notes
    *    - Requires an active rendering context
    */
    globjects::Shader * shader();

protected:
    // Virtual GpuObject functions
    virtual void onDeinit() override;

protected:
    gl::GLenum                                     m_type;   ///< Shader type
    std::string                                    m_code;   ///< Shader code
    std::unique_ptr<globjects::StaticStringSource> m_source; ///< String source for shader
    std::unique_ptr<globjects::Shader>             m_shader; ///< OpenGL shader (can be null)
};


} // namespace opengl
} // namespace rendercore
