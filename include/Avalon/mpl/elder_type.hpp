#pragma once
#include <Avalon/concept.hpp>
namespace avalon{ namespace mpl{
namespace detail{

template< class FROM, class TO >
struct ElderTypeProto
{
    using Result = std::conditional_t<
          std::is_convertible< FROM, TO >::value
        , TO
        , std::conditional_t<
              std::is_convertible< TO, FROM >::value
            , FROM
            , void
        >
    >;
};

template< class FROM, class TO >
struct ElderTypeGuard
{
    using Test = typename ElderTypeProto<FROM, TO>::Result;
    static_assert( 
          !std::is_same< Test, void >::value
        , "The two types are not convertible to each others"
    );
};

}
template<class FROM, class TO >
using ElderType = typename detail::ElderTypeGuard<FROM, TO>::Test;

}}
