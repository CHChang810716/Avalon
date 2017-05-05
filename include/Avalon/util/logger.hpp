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