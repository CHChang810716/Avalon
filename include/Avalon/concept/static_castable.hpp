#pragma once
#include <Avalon/concept/core.hpp>
namespace avalon{ namespace concept{

struct StaticCastable
{
    template<class FROM, class TO>
    auto requires( FROM&& f, TO&& t ) AVALON_EXPRS(
        static_cast<TO>(f)
    );
};

}}
