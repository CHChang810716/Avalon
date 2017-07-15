#pragma once
#include <Avalon/concept/core.hpp>
#include <Avalon/concept/static_castable.hpp>
#include <Avalon/concept/same.hpp>
#include <vector>
namespace avalon { namespace concept { 
struct RandomAccessIterator
{
    template<class T>
    auto requires( T&& o ) AVALON_EXPRS(
         *o, o++, o--, ++o, --o
        , o + int(), o - int()
        , o += int(), o -= int()
    );

};



}}
