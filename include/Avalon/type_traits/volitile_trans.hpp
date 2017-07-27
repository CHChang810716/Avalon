#pragma once
#include <type_traits>
namespace avalon{ namespace type_traits{

template<class T>
struct VolatileTrans
{
    template<class S>
    using Type = S;
};

template<class T>
struct VolatileTrans<volatile T>
{
    template<class S>
    using Type = volatile S;
};

}}
