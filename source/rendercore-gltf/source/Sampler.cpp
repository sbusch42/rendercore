
#include <rendercore-gltf/Sampler.h>


namespace rendercore
{
namespace gltf
{


Sampler::Sampler()
: m_minFilter(9729) // GL_LINEAR
, m_magFilter(9729) // GL_LINEAR
, m_wrapS(10497)    // GL_REPEAT
, m_wrapT(10497)    // GL_REPEAT
{
}

Sampler::~Sampler()
{
}

const std::string & Sampler::name() const
{
    return m_name;
}

void Sampler::setName(const std::string & name)
{
    m_name = name;
}

unsigned int Sampler::minFilter() const
{
    return m_minFilter;
}

void Sampler::setMinFilter(unsigned int filter)
{
    m_minFilter = filter;
}

unsigned int Sampler::magFilter() const
{
    return m_magFilter;
}

void Sampler::setMagFilter(unsigned int filter)
{
    m_magFilter = filter;
}

unsigned int Sampler::wrapS() const
{
    return m_wrapS;
}

void Sampler::setWrapS(unsigned int filter)
{
    m_wrapS = filter;
}

unsigned int Sampler::wrapT() const
{
    return m_wrapT;
}

void Sampler::setWrapT(unsigned int filter)
{
    m_wrapT = filter;
}


} // namespace gltf
} // namespace rendercore
