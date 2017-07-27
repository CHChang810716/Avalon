#include <gtest/gtest.h>
#include <Avalon/parallel/view/transform.hpp>
// TEST( concept, transform )
// {
//     avalon::parallel::ThreadPool tp(4);
//     avalon::parallel::view::Transform tf;
//     tf.require( avalon::parallel::view::transform(tp, [](){}) );
// }

TEST( parallel, transform )
{
    auto sleepi([]( auto&& i )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( i ) );
        return i / 2;
    });
    avalon::parallel::ThreadPool tp(4);
    std::vector<int> mss({ 500, 100, 200, 400 });
    auto ptr = avalon::parallel::view::make_async_transform_range(mss, tp, sleepi); 
    for ( auto&& v : ptr )
    {
    }

    // for( auto&& v : std::move(mss) | avalon::parallel::view::transform(tp, []( auto&& i ) 
    //     { 
    //         std::this_thread::sleep_for( std::chrono::milliseconds( i ) );
    //         return i / 2;
    //     }
    // ))
    // {
    //     // std::cout << v << std::endl;
    // }
}
