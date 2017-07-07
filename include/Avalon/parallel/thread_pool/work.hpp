#pragma once
#include <Avalon/parallel/queue.hpp>
namespace avalon{ namespace parallel{ namespace thread_pool{

class Work
{
public:
    Work(Queue& task_queue)
    : queue_ ( task_queue )
    {}
    void operator()()
    {
        while( true )
        {
            // depatch the task and execute
        }
    }
private:
    Queue& queue_;
};

}}}