
#pragma once


#include <utility>
#include <cassert>


namespace rendercore
{


template <typename T>
Cached<T>::Cached()
: m_valid(false)
, m_value(T())
{
}

template <typename T>
Cached<T>::Cached(const T & value)
: m_valid(true)
, m_value(value)
{
}

template <typename T>
Cached<T>::Cached(T && value)
: m_valid(true)
, m_value(std::move(value))
{
}

template <typename T>
bool Cached<T>::isValid() const
{
    return m_valid;
}

template <typename T>
void Cached<T>::validate() const
{
    m_valid = true;
}

template <typename T>
void Cached<T>::invalidate() const
{
    m_valid = false;
}

template <typename T>
const T & Cached<T>::value() const
{
    assert(m_valid);

    return m_value;
}

template <typename T>
T & Cached<T>::value()
{
    return m_value;
}

template <typename T>
void Cached<T>::setValue(const T & value, bool validate) const
{
    m_valid = validate;
    m_value = value;
}

template <typename T>
void Cached<T>::setValue(T && value, bool validate) const
{
    m_valid = validate;
    m_value = std::move(value);
}


} // namespace rendercore
