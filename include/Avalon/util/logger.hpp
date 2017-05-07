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
#include <Avalon/util/logger/engine.hpp>
#include <Avalon/util/logger/ostream_adapter.hpp>
#include <Avalon/const.hpp>
namespace avalon{ namespace util{


template<CVQ cvq = CVQ::immutable_v, class CHAR>
constexpr decltype(auto) tag_id_stream( 
      const CHAR* tag
    , const int& id
    , std::basic_ostream<CHAR>& open
)
{
    return logger::make_adapter<cvq>( 
          make_const_string(tag)
        , logger::id( 
            id, open
        )
    );
}

auto msg   = tag_id_stream("MSG"   , logger::msg    , std::cout);
auto warn  = tag_id_stream("WARN"  , logger::warn   , std::cout);
auto err   = tag_id_stream("ERR"   , logger::err    , std::cerr);
auto dbg   = tag_id_stream("DBG"   , logger::dbg    , std::cerr);
auto dev   = tag_id_stream<CVQ::mutable_v>("DEV"   , logger::dev    , std::cerr);

}}