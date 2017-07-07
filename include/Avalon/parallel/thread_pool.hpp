#pragma once
#include <Avalon/parallel/model/distsys/service.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <Avalon/parallel/model/distsys/task.hpp>
#include <Avalon/parallel/algo/schedule/round_robin.hpp>
#include <Avalon/util/language.hpp>
namespace avalon{ namespace parallel{

using ThreadPoolProto = model::distsys::Service<
      boost::lockfree::spsc_queue<model::distsys::Task>
    , algo::schedule::RoundRobinInt<std::size_t>
    , std::thread
>;

struct ThreadPool : public ThreadPoolProto 
{
    using Base = ThreadPoolProto;
    using Core = typename Base::Core;
    using size_type = std::size_t;
    ThreadPool( size_type n )
    : Base()
    {
        initial_threads( n );
    }
    DISABLE_COPY(ThreadPool);
    DEFAULT_MOVE(ThreadPool);
    auto join()
    {
        Base::leave();
        for( auto&& t : thread_set_ ) 
            if( t.joinable() ) 
                t.join();
        thread_set_.resize(0);
    }
    auto resize(size_type n)
    {
        join();
        Base::active();
        initial_threads( n );
    }
    ~ThreadPool()
    {
        join();
    }
protected:
    void initial_threads( size_type n )
    {
        for( size_type i (0); i < n; i ++ )
        {
            thread_set_.emplace_back([this](){ this->run(); } );
        }
        while( this->sch_algo_.get_max_id() != n )
        {
            std::this_thread::yield();
        }
    }
    std::vector<std::thread> thread_set_;
};

auto make_thread_pool( typename ThreadPool::size_type n )
{
    return ThreadPool(n);
}

}}
