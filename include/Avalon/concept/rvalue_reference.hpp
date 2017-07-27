#pragma once
#include <Avalon/concept/core.hpp>
#include <type_traits>
namespace avalon { namespace concept { 

struct RvalueReference
{
    template<class T>
    auto requires( T o ) AVALON_EXPRS(
        is_true< std::is_rvalue_reference<T>::value >
    );
}; 

}}
