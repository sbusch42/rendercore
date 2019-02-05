
#include <rendercore-opengl/Primitive.h>


namespace rendercore
{
namespace opengl
{


Primitive::Primitive(GpuObject * parent)
: GpuObject(parent)
{
}

Primitive::~Primitive()
{
}

void Primitive::onContextInit(AbstractContext *)
{
}

void Primitive::onContextDeinit(AbstractContext *)
{
}


} // namespace opengl
} // namespace rendercore
