/**
 *Copyright (C) 2017  Chia-Hua Chang
 *
 *This file is part of Avalon.
 *
 *Avalon is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *Avalon is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with Avalon.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once
#include <vector>
#include <Avalon/parallel/model/distsys/type_config.hpp>
#include <Avalon/parallel/model/distsys/task.hpp>
#include <future>
#include <map>
#include <Avalon/parallel/model/distsys/helper/get_id_type.hpp>
#include <Avalon/mpl/type.hpp>
#include <Avalon/parallel/model/distsys/helper/get_id.hpp>
#include <Avalon/parallel/model/distsys/helper/yield.hpp>
#include <Avalon/parallel/model/distsys/future.hpp>
#include <Avalon/util/language.hpp>
#include <Avalon/util/fwd.hpp>
#include <iostream>
namespace avalon {  namespace parallel { namespace model { namespace distsys{ 
template<class QUEUE, class SCH_ALGO, class CORE>
class Service
{
using This = Service<QUEUE, SCH_ALGO, CORE>;
template<class T, class S>
friend struct Future;
public:
    using Core = CORE;
    template<class T>
    using Future = avalon::parallel::model::distsys::Future<T, This>;
    Service() = default;
    DEFAULT_MOVE(Service);
    DISABLE_COPY(Service);
    auto active(){ leave_ = false; }
    template< class FUNC >
    auto submit( FUNC&& func ) // thread safe
    {
        using FuncRet = decltype(func());
        std::packaged_task<FuncRet(void)> task_storage( FWD(func) );
        auto fut( make_future( task_storage.get_future(), *this ) );
        distribute_task(Task(std::move(task_storage)));
        return fut;
    }
    static void run_task(QUEUE& q)
    {
        Task task;
        auto status = q.pop( task );
        if ( status )
        {
            task();
        }
        else
        {
            helper::yield( 
                avalon::mpl::Type<CORE>() 
            );
        }
    }
    void run()
    {
        // create a runner environment
        QUEUE queue(10); // TODO 
        auto queue_id = queue_list_.size();
        {
            std::lock_guard<std::mutex> lock( *p_queue_set_mux_ );
            queue_list_.emplace_back(&queue);
            core_map_queue_.emplace( 
                  helper::get_id( avalon::mpl::Type<CORE>() )
                , &queue
            );
            sch_algo_.set_max_id( queue_list_.size() );
        }
        while( !leave_ || !queue.empty() )
        {
            run_task( queue );
        }
    }
    auto flush() 
    { 
        for( decltype( queue_list_.size() ) i (0); i > 0; i -- )
        {
            auto ii = i - 1;
            sch_algo_.set_max_id( ii );
            while( !queue_list_.at(ii)->empty() )
            {
                helper::yield(avalon::mpl::Type<CORE>() );
            }
        }
        sch_algo_.set_max_id( queue_list_.size() );
    }
    auto leave()
    {
        leave_ = true;
        flush();
    }
    ~Service()
    {
        leave();
    }
protected:
    SCH_ALGO sch_algo_; 
private:

    using State = int;
    // inline static int working = 0;
    // inline static int leaving = 1;

    auto distribute_task(Task&& task)
    {
        auto&& qid = sch_algo_.get();
        // std::cout << qid << std::endl;
        // std::cout << queue_list_.size() << std::endl;
        queue_list_.at(qid)->push( std::move( task ) );
    }

    std::vector<QUEUE*> queue_list_;
    std::map<
          helper::GetIdType<CORE>
        , QUEUE*
    > core_map_queue_;
    std::unique_ptr<std::mutex> p_queue_set_mux_ { new std::mutex };
    bool leave_ { false };
};

}}}}
