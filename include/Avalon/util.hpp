#pragma once
namespace avalon{

template<class T>
T copy( const T& o )
{
    return o;
}
template<class T>
auto get_type_string()
{
    return __PRETTY_FUNCTION__;
}

}
