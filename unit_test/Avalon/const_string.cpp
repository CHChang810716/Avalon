#include <gtest/gtest.h>
#include <Avalon/const_string.hpp>

TEST( const_string, basic_test )
{
    constexpr avalon::ConstString cstr("hello world");
    static_assert(cstr.size() == 11, "string size is not 11");
}
TEST( const_string, ostream_test )
{
    constexpr avalon::ConstString cstr("hello world");
    std::stringstream os;
    os << cstr;
    EXPECT_EQ ( os.str(), "hello world" );
}