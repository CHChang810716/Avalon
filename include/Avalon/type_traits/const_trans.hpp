#pragma once
#include <type_traits>
namespace avalon{ namespace type_traits{

template<class T>
struct ConstTrans
{
    template<class S>
    using Type = S;
};

template<class T>
struct ConstTrans<const T>
{
    template<class S>
    using Type = const S;
};

}}
