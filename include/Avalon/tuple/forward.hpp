#pragma once
#include <tuple>
namespace avalon { namespace tuple {

template<std::size_t i, class... ARGS>
decltype(auto) forward( std::tuple<ARGS...>& tup )
{
    return std::forward< 
        std::tuple_element_t< 
            i, std::tuple<ARGS...> 
        > 
    >( std::get<i>(tup) );
}
template<std::size_t i, class... ARGS>
decltype(auto) forward( std::tuple<ARGS...>&& tup )
{
    return std::move( std::get<i>(tup) );
}

}}
