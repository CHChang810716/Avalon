#pragma once
#include <Avalon/range/core.hpp>
#include <Avalon/range/concept.hpp>
#include <Avalon/concept/core.hpp>
#include <Avalon/mpl/loop.hpp>
#include <Avalon/mpl/integer_sequence.hpp>
#include <Avalon/concept/rvalue_reference.hpp>
#include <Avalon/mpl/apply.hpp>
#include <Avalon/util/storage.hpp>

namespace avalon{ namespace range{ namespace pipe_operator {
namespace ac_ = avalon::concept;
namespace ar_ = avalon::range;
namespace au_ = avalon::util;


template<
      class RNG
    , class RNG_OP
    , ac_::require<ar_::concept::Range, RNG> = 0 
>
decltype(auto) operator| ( RNG&& rng, RNG_OP&& op )
{
    auto make_range = [
          r=avalon::util::msw( FWD(rng) )
        , rop=avalon::tuple::forward<0>(op)
    ]( auto&&... args ) mutable
    {
        return FWD(rop)(FWD(r.d), FWD(args)...);
    };
    return avalon::mpl::detail::tuple_apply_impl(
          std::move(make_range)
        , FWD(op)
        , avalon::mpl::index_for<
              1
            , std::tuple_size<std::decay_t<RNG_OP>>::value
            , 1
        > 
    );    
}


}}}

