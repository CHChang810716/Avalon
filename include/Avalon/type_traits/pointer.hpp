#pragma once
#include <type_traits>
namespace avalon { namespace type_traits {

template<class T>
struct ElementType
{
    using Result = typename T::element_type;
};

template<class T>
struct ElementType<T*>
{
    using Result = T;
};

template<class T> using ElementTypeT = typename ElementType<T>::Result;
template<class T> using DecayElementTypeT 
    = ElementTypeT<std::decay_t<T>>;
}}