#pragma once
#include <type_traits>
#include <Avalon/concept/core.hpp>
namespace avalon { namespace concept { 

struct Convertible
{
    template<class T1, class T2>
    auto requires( T1 t1, T2 t2 ) AVALON_EXPRS(
        is_true< (std::is_convertible< T1, T2 >::value) >
    );
};


}}
