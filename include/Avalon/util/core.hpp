#pragma once 
#include <memory>
namespace avalon{ namespace util{

template<class T>
auto mkuniq( T* p )
{
    return std::unique_ptr<T>( p );
}
    
}}
