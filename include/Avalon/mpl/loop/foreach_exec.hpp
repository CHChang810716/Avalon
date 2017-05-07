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
#include <Avalon/util/mutable.hpp>
#include <tuple>
namespace avalon { namespace mpl { namespace loop {

// template<class... Args>
// struct ForeachExec
// {
//     std::tuple<Args...> args_tup;
//     
//     template<class Func>
//     decltype(auto) operator() ( Func&& func )
//     {
//         return tuple_foreach ( std::forward<Func>(func), args_tup );
//     }
// };

template< class Func, class Arg1, class... Args >
inline auto foreach_exec (Func&& f, Arg1&& a1, Args&&... a )
{
    f(std::forward<Arg1>(a1));
    foreach_exec( std::forward<Func>(f), std::forward<Args>(a)...);
}

}}}
