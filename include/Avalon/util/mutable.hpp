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
#include <utility>
#include <Avalon/util/language/function_alias.hpp>
namespace avalon { namespace util {

template<class T>
struct MutableWrap
{
    mutable T d;
};
template<class T>
struct MutableWrap<T&>
{
    T& d;
};
template<class D>
auto make_mutable_wrap( D&& d )
{
    return MutableWrap<D> { std::forward<D> ( d ) };
}
FUNCTION_ALIAS( make_mutable_wrap, mmw )

}}
