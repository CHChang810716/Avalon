/**
 *Copyright (C) 2017 Chia-Hua Chang
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