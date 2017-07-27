#include <gtest/gtest.h>
#include <vector>
#include <Avalon/util/language.hpp>
#include <Avalon/range.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <Avalon/tuple.hpp>
#include <Avalon/util.hpp>
#include <iostream>
#include <tuple>
#include <Avalon/range/pipe_operator.hpp>
#include <Avalon/range/transform.hpp>
template<class T>
auto print_type()
{
    return __PRETTY_FUNCTION__;
}
TEST( mpl, index )
{
    std::cout << print_type<decltype(avalon::mpl::index_for<0, 10, 1>)>() << std::endl;

}
struct CStringIter;   
using CStringIterProto =  boost::iterator_facade<
      CStringIter
    , const char
    , std::random_access_iterator_tag
>;
struct CStringIter : public CStringIterProto
{
    using Base = CStringIterProto;

    using Core = std::tuple<const char*, std::size_t>;
    const char* itr;
    const std::size_t n;

    CStringIter( Core& c)
    : itr   ( std::get<0>(c) )
    , n     ( std::get<1>(c) )
    {}

    CStringIter( avalon::range::IteratorEnd, Core& c )
    : itr   ( std::get<0>(c) + std::get<1>(c) )
    , n     ( std::get<1>(c) )
    {}

    typename Base::reference dereference() const
    {
        return *itr;
    }

    bool equal( const CStringIter& o ) const
    {
        return o.itr == itr;
    }

    void increment()
    {
        itr ++;
    }

    void advance(typename Base::difference_type offset)
    {
        itr += offset;
    }   

    typename Base::difference_type distance_to(const CStringIter& other) const
    {
        return other.itr - itr;
    }

    void decrement()
    {
        itr --;
    }

    static decltype(auto) make_range_core( const char* str, std::size_t n )
    {
        return avalon::make_tuple( std::move(str), std::move(n) );
    }
  private:
    friend class ::boost::iterator_core_access;
};


struct NothingRop
{
    template<class RNG>
    decltype(auto) operator()(RNG&& rng) const
    {
        return FWD(rng);
    }
};

auto nothing_rop()
{
    return avalon::make_tuple( NothingRop() );
}


TEST( core, range_define )
{
    auto qq = "123456";
    auto tup = CStringIter::make_range_core( qq, 6 );
    auto rng = boost::make_iterator_range( 
          CStringIter( tup )
        , CStringIter( avalon::range::IteratorEnd(), tup )
    );
    {
        std::stringstream ss;
        for ( auto&& c : rng )
        {
            ss << c;
        }
        EXPECT_EQ( ss.str(), qq );
    }
    avalon::range::Range< CStringIter::Core, CStringIter >  rng2 ( avalon::copy(tup) );
    {
        std::stringstream ss;
        for ( auto&& c : rng2 )
        {
            ss << c;
        }
        EXPECT_EQ( ss.str(), qq );
    }
    avalon::range::Range< CStringIter::Core&, CStringIter > rng3 ( tup );
    {
        std::stringstream ss;
        for ( auto&& c : rng3 )
        {
            ss << c;
        }
        EXPECT_EQ( ss.str(), qq );
    }
    auto rng4 = avalon::range::make< CStringIter >( qq, 6 );
    {
        std::stringstream ss;
        for ( auto&& c : rng4 )
        {
            ss << c;
        }
        EXPECT_EQ( ss.str(), qq );
    }
}
using namespace avalon::range::pipe_operator;
TEST( core, operation_define )
{
    auto rng = avalon::range::make< CStringIter >( "book", 4 );

    for ( auto&& c : rng | nothing_rop() )
    {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
}
TEST( range, transform )
{
    auto rng = avalon::range::make< CStringIter >( "book", 4 );
    for( auto&& c : rng | avalon::range::transformed( 
        []( auto&& cc ){ return (int)cc; } 
    ) )
    {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
}
