#pragma once
#include <tuple>
namespace avalon { namespace tuple {
namespace detail{
template<class RET, bool>
struct ForwardHelper{};
template<class RET>
struct ForwardHelper<RET, true>
{
    template<std::size_t i, class TUP>
    inline static decltype(auto) run( TUP& tup )
    {
        return std::forward<const RET>( std::get<i>(tup) );
    }
};
template<class RET>
struct ForwardHelper<RET, false>
{
    template<std::size_t i, class TUP>
    inline static decltype(auto) run( TUP& tup )
    {
        return std::forward<RET>(std::get<i>(tup));
    }
};
}

template<
      std::size_t i
    , class TUP
    , class RRET = std::tuple_element_t<i, std::decay_t<TUP>> 
    , class FH = detail::ForwardHelper<
          RRET
        , std::is_const<std::remove_reference_t<TUP>>::value
    >
>
decltype(auto) forward( TUP&& tuple )
{
    return FH::template run<i>(tuple);
}

}}
