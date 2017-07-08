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
#include <vector>
#include <thread>
#include <Avalon/parallel/thread_pool/work.hpp>
#include <memory>
namespace avalon{ namespace parallel{ namespace thread_pool{

class ThreadContainer 
{
    using ThreadVec = std::vector<std::unique_ptr<std::thread>>;
public:
    using size_type = ThreadVec::size_type;
    ThreadContainer(
        std::vector<Work>&& work
    )
    {
        for ( auto&& w : work )
        {
            threads_.emplace_back(
                new std::thread( std::move(w) )
            );
        }
    }
    const auto view() const
    {
        std::vector< const std::thread* const > res;
        for (auto&& pt : threads_)
        {
            res.emplace_back( pt.get() );
        }
        return res;
    }

    void resize( const typename ThreadVec::size_type& n )
    {
        // if ( n > threads_.size() )
        // {
        //     for(size_type i (0); i < n - threads_.size(); i++)
        //         threads_.emplace_back( new std::thread(Work{}) );
        // }
    }
    ~ThreadContainer()
    {
        threads_.resize(0);
    }
private:
    ThreadVec threads_;
};

}}}