#include <Avalon/tuple.hpp>
#include <gtest/gtest.h>
#include <Avalon/util.hpp>

TEST( tuple, forward )
{
    std::tuple< int > t;
    std::cout << avalon::get_type_string<decltype( avalon::tuple::forward<0>(t) )>() << std::endl;
}
