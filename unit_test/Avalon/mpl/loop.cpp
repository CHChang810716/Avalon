#include <gtest/gtest.h>
#include <Avalon/mpl/loop.hpp>
#include <iostream>
namespace uml = avalon::mpl::loop;
TEST ( loop_test, foreach )
{
    uml::foreach([]( auto&& i )
    {
        std::cout << i << std::endl;
    }, 0, 0.1, "kkk" );
}
