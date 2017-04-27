#pragma once
#include <iostream>
#include <tuple>
#include <utility>
namespace avalon { namespace tuple {

template < class Tuple >
decltype(auto) head( Tuple&& t )
{
    return std::get<0>(std::forward<Tuple>(t));
}

}}
