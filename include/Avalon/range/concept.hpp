#pragma once 
#include <Avalon/range/core.hpp>
namespace avalon{ namespace range{ namespace concept {
struct Range
{
    template<class C, class I>
    int requires( const avalon::range::Range<C, I>& o )
    {}
};
}
}}
