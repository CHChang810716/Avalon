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

#include <tuple>
#include <utility>
namespace avalon { namespace tuple {
// template < std::size_t... Ns , typename... Ts >
// auto tail_impl( std::index_sequence<Ns...> , std::tuple<Ts...> t )
// {
//     return  std::make_tuple( std::get<Ns+1u>(t)... );
// }
// 
// template < typename... Ts >
// auto tail( std::tuple<Ts...> t )
// {
//     return  tail_impl( std::make_index_sequence<sizeof...(Ts) - 1u>() , t );
// }
//
}}
