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
#include <tuple>
#include <utility>
#include <Avalon/mpl/loop/foreach.hpp>
#include <Avalon/util/language.hpp>
#include <Avalon/tuple.hpp>
namespace avalon { namespace mpl { namespace loop {
template<class Func, class Tuple, std::size_t... ids>
inline decltype(auto) tuple_foreach_impl( 
      Func&& func
    , Tuple&& tuple
    , std::index_sequence< ids... >
)
{
    return foreach( std::forward<Func>(func), avalon::tuple::forward<ids>(tuple)... );
}

template<class Func, class Tuple>
inline decltype(auto) tuple_foreach( Func&& func, Tuple&& tuple )
{
    return tuple_foreach_impl( 
          std::forward<Func>(func)
        , std::forward<Tuple>(tuple)
        , std::make_index_sequence< std::tuple_size<Tuple>::value >()
    );
}

}}}
