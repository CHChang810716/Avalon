#pragma once
#include <Avalon/concept.hpp>
#include <utility>
#include <Avalon/util/language.hpp>
namespace avalon{ namespace range{
namespace detail{

constexpr struct AlwaysMove
{
    template<class RV>
    decltype(auto) operator()( RV&& value ) const
    {
        return std::move( value );
    }
} move;

constexpr struct Fowarder
{
    template<class RV>
    decltype(auto) operator()( RV&& value ) const 
    {
        return FWD(value);
    }
} forward;

}

template<class RNG, avalon::concept::require<avalon::concept::RvalueReference, RNG> = 0 >
auto create_forwarder()
{
    return detail::move;
}
template<class RNG, avalon::concept::require<avalon::concept::LvalueReference, RNG> = 0 >
auto create_forwarder()
{
    return detail::forward;
}

}}
