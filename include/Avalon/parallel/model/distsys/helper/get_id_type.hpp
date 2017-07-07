#pragma once
#include <thread>
namespace avalon{ namespace parallel { namespace model{ namespace distsys{ namespace helper{

template<class T> struct GetIdTypeProto {};

template<> 
struct GetIdTypeProto<std::thread>
{
    using Result = std::thread::id;
};

template<class T>
using GetIdType = typename GetIdTypeProto<T>::Result;

}}}}}
