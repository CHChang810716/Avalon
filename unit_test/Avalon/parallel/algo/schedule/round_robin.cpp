#include <gtest/gtest.h>
#include <Avalon/parallel/algo/schedule/round_robin.hpp>
#include <Avalon/util/logger.hpp>
#include <thread>
#include <Avalon/util/core.hpp>
TEST(round_robin, basic_test)
{
    std::vector<int> num_vec({2, 4, 6, 8, 1, 3, 5});
    auto rr = avalon::parallel::algo::schedule::make_round_robin(num_vec);
    for ( auto&& i : num_vec )
    {
        auto& n = rr.get();
        avalon::util::dev << n << std::endl;
        EXPECT_EQ(&i, &n);
    }
    for ( auto&& i : num_vec )
    {
        auto& n = rr.get();
        avalon::util::dev << n << std::endl;
        EXPECT_EQ(&i, &n);
    }
}
TEST(round_robin, parallel_test)
{
    for ( int i = 0; i < 10000; i ++)
    {
        std::vector<std::pair<
              int
            , std::unique_ptr<std::atomic<int>>
        >> num_vec;
        for ( int i = 0; i < 100; i++ )
        {
            num_vec.emplace_back(
                i, nullptr
            );
            num_vec.back().second = std::move(
                std::unique_ptr<std::atomic<int>>(
                    new std::atomic<int>(0)
                )
            );
        }

        auto rr = avalon::parallel::algo::schedule::make_round_robin(num_vec);
        std::thread t0([&num_vec, &rr]() mutable
        {
            for ( int i = 0; i < 10; i ++ )
                for ( auto&& i : num_vec )
                {
                    auto& n = rr.get();
                    (*n.second) ++;
                }
        });
        std::thread t1([&num_vec, &rr]() mutable
        {
            for ( int i = 0; i < 10; i ++ )
                for ( auto&& i : num_vec )
                {
                    auto& n = rr.get();
                    (*n.second)++;
                }
        });
        t0.join();
        t1.join();
        int sum(0);
        for ( auto&& n : num_vec)
        {
            sum += *(n.second);
        }
        EXPECT_EQ(sum, num_vec.size() * 2 * 10);
    }
}