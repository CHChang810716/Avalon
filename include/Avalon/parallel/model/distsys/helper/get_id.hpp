#pragma once
#include <Avalon/mpl/type.hpp>
#include <thread>
namespace avalon::parallel::model::distsys::helper{

decltype(auto) get_id( const avalon::mpl::Type<std::thread>& thread_type )
{
    return std::this_thread::get_id();
}

}
