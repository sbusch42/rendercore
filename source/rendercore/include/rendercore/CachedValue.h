
#pragma once


#include <rendercore/rendercore_api.h>


namespace rendercore
{


/**
*  @brief
*    Extends a value of arbitrary type by an invalidation flag.
*
*    The cached value is intended for use in lazy initialization, getter or setters
*    and removes the overhead of adding 'dirty', 'valid', or 'update' flags to your
*    class. Especially when having multiple values, cached value allows per value
*    validity flags. Note: all setters of this class are const, simplifying const
*    getters in classes by holding a mutable value as member.
*
*    Typeical usage of the CachedValue:
*    \code{.cpp}
*
*        // on update
*        lazyValue.invalidate();
*        ...
*        // example getter
*        if (!lazyValue.isValid())
*            lazyValue.setValue(complexCalculationForLazyValue());
*
*        return lazyValue.value();
*    \endcode
*
*  @tparam T
*    The wrapped value type
*/
template <typename T>
class RENDERCORE_TEMPLATE_API CachedValue
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @remarks
    *    Creates an empty, invalid cached value
    */
    CachedValue();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    The value
    *
    *  @remarks
    *    Creates an initialized, valid cached value
    */
    CachedValue(const T & value);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    The value
    *
    *  @remarks
    *    Creates an initialized, valid cached value
    */
    CachedValue(T && value);

    /**
    *  @brief
    *    Check if vaue is valid
    *
    *  @return
    *    'true' if value is valid, else 'false'
    */
    bool isValid() const;

    /**
    *  @brief
    *    Get value
    *
    *  @return
    *    The value
    */
    T & value();

    /**
    *  @brief
    *    Get value
    *
    *  @return
    *    The value
    */
    const T & value() const;

    /**
    *  @brief
    *    Set value
    *
    *  @param[in] value
    *    The value
    *  @param[in] validate
    *    The validation status
    */
    void setValue(const T & value, bool validate = true) const;

    /**
    *  @brief
    *    Set value
    *
    *  @param[in] value
    *    The value
    *  @param[in] validate
    *    The validation status
    */
    void setValue(T && value, bool validate = true) const;

    /**
    *  @brief
    *    Set valid state to 'true'
    */
    void validate() const;

    /**
    *  @brief
    *    Set valid state to 'false'
    */
    void invalidate() const;

protected:
    mutable bool m_valid; ///< Valid status
    mutable T    m_value; ///< Value
};


} // namespace rendercore


#include <rendercore/CachedValue.inl>
