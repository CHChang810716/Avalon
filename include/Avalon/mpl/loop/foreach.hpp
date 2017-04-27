#pragma once
#include <initializer_list>
#include <Avalon/util/fwd.hpp>
namespace avalon { namespace mpl { 
namespace loop {
template< class Func, class... Args >
auto foreach( Func&& f, Args&&... args )
{
    return (void)std::initializer_list<int> {
        ( f(FWD(args)), 0 )...
    };
}

}
}}
