#pragma once
#include <utility>
#include <UCW/util/language/function_alias.hpp>
namespace UCW { namespace util {

template<class T>
struct MutableWrap
{
    mutable T d;
};
template<class T>
struct MutableWrap<T&>
{
    T& d;
};
template<class D>
auto make_mutable_wrap( D&& d )
{
    return MutableWrap<D> { std::forward<D> ( d ) };
}
FUNCTION_ALIAS( make_mutable_wrap, mmw )

}}
