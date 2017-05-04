#pragma once 
#include <Avalon/util/logger/engine.hpp>
#include <Avalon/util/logger/OstreamAdapter.hpp>
namespace avalon{ namespace util{


constexpr decltype(auto) tag_id_stream( 
      const ConstString& tag
    , const int& id
    , std::ostream& open
)
{
    return logger::make_adapter( tag, logger::id( 
        id, open
    ));
}

auto msg   = tag_id_stream("MSG"   , logger::msg    , std::cout);
auto warn  = tag_id_stream("WARN"  , logger::warn   , std::cout);
auto err   = tag_id_stream("ERR"   , logger::err    , std::cerr);
auto dbg   = tag_id_stream("DBG"   , logger::dbg    , std::cerr);
auto dev   = tag_id_stream("DEV"   , logger::dev    , std::cerr);

}}