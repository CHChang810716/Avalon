#pragma once
#include <boost/range/iterator_range.hpp>
#include <Avalon/concept/reference.hpp>
#include <Avalon/util/language.hpp>
namespace avalon{ namespace range{

namespace ac_ = avalon::concept;

struct IteratorEnd{};


template<class CORE>
struct RangeProto
{
    CORE core;
};

template<class CORE, class ITR>
struct Range : 
      public RangeProto<CORE>
{
    using This = Range<CORE, ITR>;
    using iterator = ITR;
    using reference = typename std::iterator_traits< ITR >::reference;
    using value_type = typename std::iterator_traits< ITR >::value_type;
    Range( CORE&& core )
    : RangeProto<CORE>{ FWD( core ) }
    {}
    auto begin()
    {
        return ITR( RangeProto<CORE>::core );
    }
    auto end()
    {
        return ITR( IteratorEnd{}, RangeProto<CORE>::core );
    }
    auto begin() const
    {
        return const_cast< This& >( *this ).begin();
    }
    auto end() const 
    {
        return const_cast< This& >( *this ).end();
    }
    template<class I>
    auto operator[]( I i ) -> decltype( *(begin() + i) )
    {
        return *(begin() + i);
    }
};

template<class T, class... ARGS> // check T match iterator concept and has create
auto make( ARGS&&... args )
{
    auto&& core = T::make_range_core( FWD(args)... );
    return Range< 
          decltype( T::make_range_core( FWD(args)... ) ) 
        , T
    >( FWD(core) );
}




}
}
