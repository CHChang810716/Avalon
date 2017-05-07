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
namespace avalon { 
template<class CHAR>
class ConstStringProto
{
public:
    using value_type = CHAR;
    using size_type = std::size_t;
    constexpr ConstStringProto( const CHAR* str )
    : str_ ( str )
    {}
    constexpr size_type size() const
    {
        size_type i(0); 
        for( i = 0; str_[i] != '\0'; i ++ );
        return i;
    }
    constexpr decltype(auto) c_str() const
    {
        return str_;
    }
private:
    const CHAR* str_;
};

template<class CHAR>
constexpr auto make_const_string(const CHAR* cstr )
{
    return ConstStringProto<CHAR>(cstr);
}

template<class T, class CHAR>
decltype(auto) operator<<(T&& o, const ConstStringProto<CHAR>& str )
{
    return o << str.c_str();
}
using ConstString = ConstStringProto<char>;

    
}