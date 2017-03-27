#pragma once
#include <tuple>
#include <utility>
#include <UCW/mpl/loop/foreach_exec.hpp>
namespace UCW { namespace mpl { namespace loop {
template<class Func, class Tuple, std::size_t... ids>
inline decltype(auto) tuple_foreach_impl( 
      Func&& func
    , Tuple&& tuple
    , std::index_sequence< ids... >
)
{
    return foreach_exec( std::forward<Func>(func), std::get<ids>(tuple)... );
}

template<class Func, class Tuple>
inline decltype(auto) tuple_foreach( Func&& func, Tuple&& tuple )
{
    return tuple_foreach_impl( 
          std::forward<Func>(func)
        , std::forward<Tuple>(tuple)
        , std::make_index_sequence< std::tuple_size<Tuple>::value >()
    );
}

}}}
