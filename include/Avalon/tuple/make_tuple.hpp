#pragma once
#include <tuple>
namespace UCW { namespace tuple {

template<class... Args>
auto make_tuple( Args&&... args )
{
    return std::tuple<Args...>( std::forward<Args>(args)... );
}

}}
