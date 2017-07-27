#pragma once
#include <tuple>
#include <Avalon/tuple.hpp>
#include <boost/iterator_adaptors.hpp>
#include <Avalon/range/core.hpp>
#include <Avalon/mpl/integer_sequence.hpp>
#include <Avalon/range/iterator_tag_order.hpp>
namespace avalon{ namespace range{

template< class CORE > struct TransformIterator; // forward declartion

template< class CORE >
using TransformIteratorProto = boost::iterator_adaptor<
      TransformIterator<CORE>
    , typename CORE::BaseIterator
    , typename CORE::Value
    , typename CORE::IteratorCategory
    , typename CORE::Reference
    , typename CORE::Difference
>;
template<class RNG, class FUNC, class UPPER >
struct TransformIteratorCore
{
    RNG base_range;
    FUNC function;
    using BaseRange         = RNG;
    using Function          = FUNC;
    using BaseIterator      = typename std::remove_reference_t<RNG>::iterator;
    using Reference         = decltype(function(
        std::declval<
            typename std::iterator_traits< 
                BaseIterator 
            >::reference
        >()
    ));
    using IteratorCategory  
        = avalon::range::LowerOrder< 
              typename std::iterator_traits< BaseIterator >::iterator_category
            , UPPER
        >;
    using Value             = decltype(function(
        std::declval<
            typename std::iterator_traits< 
                BaseIterator 
            >::value_type
        >()
    ));
    using Difference        = typename std::iterator_traits<BaseIterator>::difference_type;
};

template< class CORE >
struct TransformIterator : public TransformIteratorProto< CORE >
{
private:
    friend class boost::iterator_core_access;
    using Base = TransformIteratorProto< CORE >;
    using Function = typename CORE::Function;
    using BaseRange = typename CORE::BaseRange;
    decltype(auto) dereference() const
    {
        return (*func_) ( *this->base_reference() );
    }
    Function* const func_ { nullptr };
public:
    TransformIterator( CORE& core )
    : Base  ( core.base_range.begin()   )
    , func_ ( &core.function            )
    {}
    TransformIterator( avalon::range::IteratorEnd, CORE& core )
    : Base  ( core.base_range.end() )
    , func_ ( nullptr )
    {}

    template<class RNG, class FUNC, class TAG>
    static auto make_range_core( RNG&& rng, FUNC&& func, TAG upper )
    {
        return TransformIteratorCore< RNG, FUNC, TAG >{ FWD(rng), FWD(func) };
    }
};

constexpr struct Transform
{
    template<class RNG, class FUNC, class TAG>
    decltype(auto) make_transform_range( RNG&& rng, FUNC&& func, TAG upper ) const 
    {
        return avalon::range::make< 
            TransformIterator<
                TransformIteratorCore< RNG, FUNC, TAG >
            >
        >( FWD( rng ), FWD( func ), upper ); 
    }
    template<class RNG, class FUNC, class TAG>
    decltype(auto) operator()(RNG&& rng, FUNC&& func, TAG upper) const
    {
        return make_transform_range( FWD(rng), FWD(func), upper );
    } 
} transform;

constexpr struct TransformPipeOp
{
    template<class FUNC, class TAG = boost::random_access_traversal_tag>
    decltype(auto) operator()( FUNC&& func, TAG upper = boost::random_access_traversal_tag{}) const
    {
        return avalon::make_tuple( transform, FWD(func), upper );
    }
} transformed;

}}
