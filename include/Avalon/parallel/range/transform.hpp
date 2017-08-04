#pragma once
#include <Avalon/parallel/model/distsys/future.hpp>
#include <vector>
#include <Avalon/parallel/thread_pool.hpp>
#include <Avalon/concept/rvalue_reference.hpp>
#include <Avalon/tuple.hpp>
#include <Avalon/concept/core.hpp>
#include <Avalon/concept/same.hpp>
#include <Avalon/util/print_type.hpp>
#include <Avalon/range/concept.hpp>
#include <Avalon/range/pipe_operator.hpp>
#include <Avalon/range/transform.hpp>
#include <Avalon/range/forward.hpp>
namespace avalon{ namespace parallel{ namespace range{
    namespace ac_ = avalon::concept;

    constexpr struct Transform
    {
        template<class RNG, class FUNC> //, AVALON_CONCEPT_REQUIRE__(avalon::range::concept::Range, RNG)>
        decltype(auto) operator() ( RNG&& rng, FUNC&& func, avalon::parallel::ThreadPool& tp ) const
        {
            using namespace avalon::range::pipe_operator;
            using TransReturn = decltype(func(*rng.begin()));
            auto value_forward = avalon::range::create_forwarder< RNG&& >();
            std::vector< avalon::parallel::ThreadPool::Future< TransReturn > > fut_list;
            for ( auto&& v : rng )
            {
                fut_list.emplace_back( tp.submit([f = FWD(func), in = FWD(v), value_forward ]() mutable -> decltype(auto){ 
                    return f( value_forward( FWD(in) ) ); 
                }) );
            }
            return avalon::range::transform( std::move(fut_list), []( auto&& v ) -> decltype(auto)
            {
                return v.sync();
            });
        }
    } transform;

    constexpr struct TransformPipeRopP
    {
        template< class FUNC >
        decltype(auto) operator() ( FUNC&& func, avalon::parallel::ThreadPool& tp ) const
        {
            return avalon::make_tuple( transform, FWD(func), tp );
        }
    } transformed;
}}}
