
#include <rendercore-opengl/Material.h>


namespace rendercore
{
namespace opengl
{


Material::Material(GpuObject * parent)
: GpuObject(parent)
{
}

Material::~Material()
{
}

void Material::onContextInit(AbstractContext *)
{
}

void Material::onContextDeinit(AbstractContext *)
{
}


} // namespace opengl
} // namespace rendercore
