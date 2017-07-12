#include <Avalon/parallel/thread_pool.hpp>
#include <sstream>
#include <gtest/gtest.h>
template<class FUNC>
auto time( FUNC&& f )
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    f();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    return elapsed_seconds.count();
}
// TEST( thread_pool, resize )
// {
//     nucleona::parallel::ThreadPool tp  = nucleona::parallel::make_thread_pool(4);
//     EXPECT_TRUE( tp.resize_pool( 7 ) );
//     nucleona::parallel::ThreadPool tp2 = nucleona::parallel::make_thread_pool(3);
//     EXPECT_FALSE( tp2.resize_pool(4) );
//     EXPECT_ANY_THROW( { nucleona::parallel::make_thread_pool( 2 ); } );
//     EXPECT_ANY_THROW( { nucleona::parallel::make_thread_pool( ); } );
// }
TEST( thread_pool, basic_test )
{
    avalon::parallel::ThreadPool tp = avalon::parallel::make_thread_pool(2);
    std::stringstream expect_not;
    std::stringstream subject;
    std::mutex subject_mux;
    for ( int i(0); i < 10; i++ )
    {
        for ( int j = 0; j < 10; j ++ )
            expect_not << i << '\t' << j << '\t' << i * j << std::endl;
    }
    for ( int i(0); i < 10; i++ )
    {
        tp.submit( [i, &subject, &subject_mux]()
        {
            for ( int j = 0; j < 10; j ++ )
            {
                std::lock_guard<std::mutex> lock( subject_mux );
                subject << i ;
                subject << '\t';
                subject << j;
                subject << '\t';
                subject << i * j;
                subject << std::endl;
                std::this_thread::sleep_for( std::chrono::milliseconds(std::rand() % 100) );
            }

        });
    }
    // std::cout << expect_not.str() << std::endl;
    // std::cout << subject.str() << std::endl;
    tp.flush();
    EXPECT_NE( expect_not.str(), subject.str() );
}
TEST( thread_pool, performance )
{
    const auto datasize = 8;
    avalon::parallel::ThreadPool tp = avalon::parallel::make_thread_pool(2);
    std::vector<int> vec(datasize);
    time([&vec]()
    {
        for( auto&& v : vec )
        {
            v = std::rand() % 3;
        }
    });

    auto single_thread = time([&vec](){
        for( auto&& v : vec )
        {
            std::this_thread::sleep_for( std::chrono::seconds(v) );
        }
    });
    std::cout << single_thread << std::endl;

    auto segsize = vec.size() / 2;
    auto two_thread = time(
        [&vec,  &tp, &segsize]()
        {
            std::vector< avalon::parallel::ThreadPool::Future<void> > fut_vec;
            for ( std::size_t i (0); i < vec.size(); i += segsize )
            {
                fut_vec.emplace_back( tp.submit([&vec, i, &segsize]
                {
                    for ( std::size_t j = i; j < i + segsize; j ++ ) 
                    {
                        std::this_thread::sleep_for( std::chrono::seconds(vec.at(j)) );
                    }
                }) );
            }
            for( auto&& fut : fut_vec )
            {
                fut.sync();
            }
        }
    );
    std::cout << two_thread << std::endl;
    auto speed_comp_rate = ( single_thread / two_thread );
    std::cout << "speed_rate: " << speed_comp_rate << std::endl;
    // EXPECT_TRUE( speed_comp_rate > 1.4 );
}
uint64_t fib( uint64_t n )
{
    return n < 2 ? n : fib( n - 1 ) + fib ( n - 2 );
}
uint64_t fib( avalon::parallel::ThreadPool& tp, uint64_t n )
{
    if ( n < 40 ) return fib(n);

    // std::cout << "fib(" << n << ") on " << std::this_thread::get_id() << std::endl;
    if ( n < 2 ) return n;
    else
    {
        auto af = tp.submit(
                [&tp, n] (){ return fib( tp, n - 1 ); }
                );
        auto b = fib( tp, n - 2 );
        auto a = af.sync();

        return a + b;
    }
}
TEST( thread_pool, recursive )
{
    auto tp = avalon::parallel::make_thread_pool(4);
    uint64_t exp = 0;
    auto exp_time = time([&exp](){ exp = fib( 46 );} );
    std::cout << exp_time << std::endl;
    std::cout << exp << std::endl;

    uint64_t ans = 0;
    auto ans_time = time([&ans, &tp](){ ans = fib( tp, 46 );} );

    std::cout << ans_time << std::endl;
    std::cout << ans << std::endl;

    EXPECT_EQ( ans, exp );
    auto speed_comp_rate = ( exp_time / ans_time );
    std::cout << "speed_rate: " << speed_comp_rate << std::endl;
    // EXPECT_TRUE( speed_comp_rate > 3 );
}
