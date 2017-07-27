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
    , public boost::iterator_range<ITR>
{
    Range( CORE&& core )
    : RangeProto<CORE>{ FWD( core ) }
    , boost::iterator_range<ITR>( 
        boost::make_iterator_range(
              ITR( RangeProto<CORE>::core )
            , ITR( IteratorEnd{}, RangeProto<CORE>::core )
        )
    )
    {}
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
