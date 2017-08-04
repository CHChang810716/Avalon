#include <gtest/gtest.h>
#include <Avalon/parallel/range/transform.hpp>
// TEST( concept, transform )
// {
//     avalon::parallel::ThreadPool tp(4);
//     avalon::parallel::view::Transform tf;
//     tf.require( avalon::parallel::view::transform(tp, [](){}) );
// }

TEST( parallel, transform )
{
    using namespace avalon::range::pipe_operator;
    auto sleepi([]( auto&& i )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( i ) );
        return i / 2;
    });
    avalon::parallel::ThreadPool tp(4);
    std::vector<int> mss({ 500, 100, 200, 400 });
    auto rng = mss | avalon::parallel::range::transformed(sleepi, tp);
    for ( auto&& v : rng )
    {
        std::cout << v << std::endl;    
    };
}
