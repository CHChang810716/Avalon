/**
 *Copyright (C) 2017  Chia-Hua Chang
 *
 *This file is part of Avalon.
 *
 *Avalon is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *Avalon is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with Avalon.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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