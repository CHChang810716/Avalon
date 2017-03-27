#include <gtest/gtest.h>
#include <UCW/mpl/loop.hpp>
#include <iostream>
namespace uml = UCW::mpl::loop;
TEST ( loop_test, foreach )
{
    uml::foreach([]( auto&& i )
    {
        std::cout << i << std::endl;
    }, 0, 0.1, "kkk" );
}
