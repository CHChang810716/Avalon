#pragma once
#include <Avalon/tuple.hpp>
namespace avalon{ namespace mpl{
template<class FUNC, class... ARGS>
inline decltype(auto) apply( FUNC&& func, ARGS&&... args )
{
    return FWD(func)(FWD(args)...);
}
namespace detail{
template<class FUNC, class TUPLE, std::size_t... ids >
inline decltype(auto) tuple_apply_impl( 
      FUNC&& func
    , TUPLE&& tup
    , std::index_sequence< ids... > 
)
{
    return apply( FWD(func), avalon::tuple::forward<ids>(tup)... );
}
}
template<class FUNC, class TUPLE>
inline decltype(auto) tuple_apply( FUNC&& func, TUPLE&& tup )
{
    return detail::tuple_apply_impl( 
          std::forward<FUNC>(func)
        , std::forward<TUPLE>(tup)
        , std::make_index_sequence< std::tuple_size<TUPLE>::value >()
    );


}

}}
