#pragma once
#include <tuple>
namespace avalon { namespace tuple {

template<class... Args>
auto make_tuple( Args&&... args )
{
    return std::tuple<Args...>( std::forward<Args>(args)... );
}

}}
