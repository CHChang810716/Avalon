#pragma once
#include <Avalon/concept/core.hpp>
#include <type_traits>
namespace avalon { namespace concept { 

struct Same
{
    template<class T1, class T2>
    auto requires( T1 t1, T2 t2 ) AVALON_EXPRS(
        ( is_true< std::is_same<T1, T2>::value > )
    );
};

}}
