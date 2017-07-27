#pragma once

namespace avalon{ namespace util{

template<class T>
auto print_type()
{
    return __PRETTY_FUNCTION__;
}
template<class T>
auto print_type(T&& o)
{
    return __PRETTY_FUNCTION__;
}

}}
