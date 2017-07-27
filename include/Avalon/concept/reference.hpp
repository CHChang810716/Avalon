#pragma once
#include <type_traits>
#include <Avalon/concept/core.hpp>
namespace avalon{ namespace concept{

struct Reference
{
    template<class T>
    auto requires( T o ) AVALON_EXPRS(
        is_true< std::is_reference<T>::value >
    );
};


}}
