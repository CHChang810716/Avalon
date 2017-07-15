#include <gtest/gtest.h>
#include <Avalon/concept/iterator.hpp>
#include <Avalon/concept/expr_validator.hpp>
#include <Avalon/util/language.hpp>
#include <Avalon/concept/static_castable.hpp>
#include <Avalon/concept/same.hpp>
using namespace avalon::concept;
struct IntPushBackAble
{
    template<class T>
    auto requires( T o ) AVALON_EXPRS (
         o.push_back( int() )
    );
};
struct StdVector
{
    template<class... T>
    int helper( const std::vector<T...>& vec );

    template<class T>
    auto requires( T o ) AVALON_EXPRS(
        helper( o )
    );
        
};
struct UserDefineType{};
template<class T, typename concept_requires< RandomAccessIterator, T>::type = 0 >
int func( T&& o )
{
    return 1;
}

template<class T, AVALON_CONCEPT_REQUIRE_NOT_( RandomAccessIterator, T )>
int func( T&& o )
{
    return 0;
}
template<class T, AVALON_CONCEPT_REQUIRE_( IntPushBackAble, T ) >
int func2( T&& o )
{
    return 1;
}

template<class T, AVALON_CONCEPT_REQUIRE_NOT_( IntPushBackAble, T )>
int func2( T&& o )
{
    return 0;
}
template<class T, AVALON_CONCEPT_REQUIRE_( StdVector, T ) >
int func3( T&& o )
{
    return 1;
}
template<class T, AVALON_CONCEPT_REQUIRE_NOT_( StdVector, T ) >
int func3( T&& o )
{
    return 0;
}

TEST( has_require, basic_test )
{
    auto sat = HasRequires<
          RandomAccessIterator
        , void( std::vector<int>::iterator& )
    >::value;
    auto unsat = HasRequires<
          RandomAccessIterator
        , void( int )
    >::value;
    EXPECT_TRUE( sat );
    EXPECT_FALSE( unsat );
}
TEST( concept, expr_list )
{
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    std::vector<int> vec{ AVALON_VALID_EXPRS( a, b, c, d ) };
    for ( auto&& i : vec )
    {
        EXPECT_EQ(i, 0 );
    }
}
TEST( define_concept, random_access_iterator )
{
    std::vector<int> vec;
    EXPECT_EQ( func(0), 0 );
    EXPECT_EQ( func(vec.begin()), 1);
}
TEST( define_concept, push_back_able)
{
    auto sat = satisfied<IntPushBackAble, std::vector<int>>;
    auto unsat = satisfied<IntPushBackAble, int>;
    EXPECT_TRUE( sat );
    EXPECT_FALSE( unsat );
    EXPECT_EQ( func2(0), 0);
    EXPECT_EQ( func2(std::vector<int>{}), 1);
    auto sat2 = satisfied<IntPushBackAble, std::vector<int>&>;
    EXPECT_TRUE( sat2 );
}
TEST( define_template_type_concept, vector )
{
    auto sat = satisfied<StdVector, std::vector<UserDefineType>>;
    EXPECT_TRUE( sat );
    EXPECT_EQ( func3(0), 0 );
    EXPECT_EQ( func3(std::vector<UserDefineType>()), 1 );
}
TEST( concept, static_castable )
{
    auto sat = satisfied< 
        StaticCastable
        , bool, int
    >;
    auto unsat = satisfied<
        StaticCastable
        , int, std::string
    >;
        
    EXPECT_TRUE( sat );
    EXPECT_FALSE( unsat );
}
TEST( consept, same )
{
    auto sat = satisfied< 
        Same
        , bool, bool
    >;
    auto unsat = satisfied< 
        Same
        , bool, int
    >;
    EXPECT_TRUE( sat );
    EXPECT_FALSE( unsat );

} 
