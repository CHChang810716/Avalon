#pragma once
#include <type_traits>
namespace avalon{ namespace type_traits{

template<class T>
struct RefTrans
{
    template<class S>
    using Type = S;
};

template<class T>
struct RefTrans<T&>
{
    template<class S>
    using Type = S&;
};

template<class T>
struct RefTrans<T&&>
{
    template<class S>
    using Type = S&&;
};
}}
