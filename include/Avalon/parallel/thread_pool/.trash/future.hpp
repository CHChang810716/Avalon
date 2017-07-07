#pragma once
// #include <future>
// #include <Avalon/parallel/thread_pool/thread_container.hpp>
// namespace avalon{ namespace parallel{ namespace thread_pool{
// 
// template<class T>
// class Future : protected std::future<T>
// {
//     bool is_recursive_task()
//     {
//     }
// public:
//     Future(int tstid, const TaskServer& ts)
//     : task_submitter_thread_id_ (tstid)
//     , task_server_ ( ts )
//     {}
//     decltype(auto) operator()()
//     {
//         if( !is_recursive_task() )
//         {
//             // post this function
//             // yield 
//         }
//         this->wait();
//         return this->get();
//     }
// private:
//     const int task_submitter_thread_id_;
//     const std::vector< const std::thread* const > threads_;
//     const TaskServer task_server_;
// };
// 
// }}}