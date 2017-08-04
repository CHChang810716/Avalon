#pragma once 
#include <Avalon/range/core.hpp>
namespace avalon{ namespace range{ namespace concept {
struct Range
{
    template<class RNG>
    auto requires( RNG&& rng ) AVALON_EXPRS(
        *rng.begin(), *rng.end()
    );
};
}
}}
