#pragma once
#include <Avalon/parallel/model/distsys/future.hpp>
#include <vector>
#include <Avalon/parallel/thread_pool.hpp>
#include <range/v3/all.hpp>
#include <Avalon/concept/rvalue_reference.hpp>
#include <Avalon/tuple.hpp>
#include <Avalon/concept/core.hpp>
#include <Avalon/concept/same.hpp>
#include <Avalon/util/print_type.hpp>
namespace avalon{ namespace parallel{ namespace view{
namespace ac_ = avalon::concept;
template<class T, class FUNC>
struct AsyncTransformRange
: public ranges::view_facade< AsyncTransformRange< T, FUNC > >
{
    using Future = avalon::parallel::ThreadPool::Future< T >;
    using FutList = std::vector< Future >;
    template<
          class INPUT_TASK_RANGE
//         , int a = ac_::require<ac_::RvalueReference, INPUT_TASK_RANGE>
    >
    AsyncTransformRange( 
          INPUT_TASK_RANGE&& input_task_range
        , avalon::parallel::ThreadPool& tp
        , FUNC&& func
    )
    : func_ ( FWD(func) )
    {
        auto cvr_fwd = avalon::util::make_cvr_fwder<INPUT_TASK_RANGE&&>();
        for ( auto&& task_input : input_task_range )
        {
            // p_fut_list_->emplace_back(
            //     [ this, input=cvr_fwd(task_input), cvr_fwd ]()
            //     {
            //         avalon::util::dev << avalon::util::print_type<decltype(input)>() << std::endl;
            //         return func_( cvr_fwd( input ) );
            //     }
            // );
        }
        itr_ = p_fut_list_->begin();
    }
  private:
    friend ranges::range_access;
    std::shared_ptr<FutList> p_fut_list_{ new FutList() };
    typename FutList::iterator itr_;
    FUNC func_;
    Future const& read() const 
    {
        // return itr_->sync();
        return *itr_;
    }
    bool equal( ranges::default_sentinel ) const 
    {
        return itr_ == p_fut_list_->end();
    }
    void next() { ++ itr_; }
};
template<
      class INPUT_TASK_RANGE
    , class FUNC
//     , int a = ac_::require<ac_::RvalueReference, INPUT_TASK_RANGE>
> auto make_async_transform_range( 
      INPUT_TASK_RANGE&& input_task_range
    , avalon::parallel::ThreadPool& tp 
    , FUNC&& func
)
{
    return AsyncTransformRange<
          INPUT_TASK_RANGE
        , FUNC 
    >( FWD( input_task_range ), tp, FWD( func ) );
}
struct Transform
{
    template<class... T>
    int helper( std::tuple<Transform, T...> tup );
    template<class T >
    auto requires( T o) AVALON_EXPRS(
        helper( o )
    );
};
template<class FUNC>
auto transform( avalon::parallel::ThreadPool& tp, FUNC&& func )
{
    return avalon::make_tuple( Transform{}, tp, FWD(func) );
}
template<class INPUT_RNG, class TUP, concept::require<Transform, TUP> = 0 >
decltype(auto) operator|( INPUT_RNG&& rng, TUP&& tup )
{
    return make_async_transform_range( 
          FWD(rng)
        , FWD(std::get<1>(tup))
        , FWD(std::get<2>(tup))
    );
}

}}}
