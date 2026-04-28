/// @file system/details/is_template_base_of.h
#ifndef _is_template_base_of_h_
#define _is_template_base_of_h_


#include "defines.h"


namespace System
{
namespace Details
{

/// Represents implementation of IsTemplateBaseOf.
/// @tparam Base Not instantiated base template class.
/// @tparam Derived Instantiated base derived template class.
template <template <typename...> class Base, typename Derived>
struct IsTemplateBaseOfImpl
{
    /// Using SFINAE, determines the inheritance of the Derived class from the Base class.
    /// @tparam Ts Parameter pack containing a template arguments list deduced from Derived class.
    template <typename... Ts>
    static constexpr std::true_type test(const Base<Ts...>*);
    /// Non-template overload that determines that the Derived class does not inherit from the Base class if the template version of this function was not substituted.
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<Derived*>()));
};

/// Represents std::is_base_of<Base, Derived> counterpart that determine the inheritance of not instantiated Base template class from instantiated Derived template class. Will fail with multiple inheritance or non-public inheritance from Base.
/// @tparam Base Not instantiated base template class.
/// @tparam Derived Instantiated derived template class.
template <template <typename...> class Base, typename Derived>
using IsTemplateBaseOf = typename IsTemplateBaseOfImpl<Base, Derived>::type;

} //namespace Details
} //namespace System


#endif //_is_template_base_of_h_
