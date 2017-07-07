#pragma once
#include <Avalon/mpl/type.hpp>
#include <thread>
namespace avalon::parallel::model::distsys::helper{

auto yield( const avalon::mpl::Type<std::thread>& )
{
    std::this_thread::yield();
}

}
