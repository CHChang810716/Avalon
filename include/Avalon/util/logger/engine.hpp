#pragma once
#include <iostream>
#include <Avalon/util/logger/null_buffer.hpp>
#include <Avalon/const.hpp>
namespace avalon{ namespace util{ namespace logger{
constexpr auto msg  = 0;
constexpr auto warn = 1;
constexpr auto err  = 2;
constexpr auto dbg  = 3;
constexpr auto dev  = 4;
constexpr bool is_in_open_port( const int& id)
{
    for ( auto i : { OPEN_LOG_PORT } )
    {
        if ( id == i )
            return true;
    }
    return false;
}
constexpr decltype(auto) id( const int& i, std::ostream& open = std::cout )
{
    return is_in_open_port(i) ? open : nout;
}
}}}