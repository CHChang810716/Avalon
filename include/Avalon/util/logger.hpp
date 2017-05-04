#pragma once 
#include <Avalon/util/logger/engine.hpp>
namespace avalon{ namespace util{

auto& msg   = logger::id(logger::msg    , std::cout);
auto& warn  = logger::id(logger::warn   , std::cout);
auto& err   = logger::id(logger::err    , std::cerr);
auto& dbg   = logger::id(logger::dbg    , std::cerr);
auto& dev   = logger::id(logger::dev    , std::cerr);

}}