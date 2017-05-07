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
#include <type_traits>
namespace avalon { namespace type_traits {

template<class T>
struct ElementType
{
    using Result = typename T::element_type;
};

template<class T>
struct ElementType<T*>
{
    using Result = T;
};

template<class T> using ElementTypeT = typename ElementType<T>::Result;
template<class T> using DecayElementTypeT 
    = ElementTypeT<std::decay_t<T>>;
}}