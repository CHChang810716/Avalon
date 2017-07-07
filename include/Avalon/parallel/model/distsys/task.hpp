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
#include <future>
#include <Avalon/util/core.hpp>
namespace avalon {  namespace parallel { namespace model { namespace distsys{ 
class Task
{
    struct StorageProto
    {
        virtual void call() = 0;
    };
    template<class T>
    struct Storage : public StorageProto
    {
        Storage(  std::packaged_task<T>&& storage )
        : storage_( std::move( storage ) )
        {}

        virtual void call()
        {
            storage_();
        }
    private:
        std::packaged_task<T> storage_;
    };
public:
    Task()
    : storage_ ( nullptr )
    {}
    Task( const Task& t )
    : storage_ ( std::move( const_cast<Task&>(t).storage_ ) )
    {}
    auto& operator=( const Task& t )
    {
        storage_ = std::move( const_cast<Task&>(t).storage_ );
        return *this;
    }
    template<class T>
    Task( std::packaged_task<T>&& storage ) 
    : storage_ ( new Storage<T>(std::move(storage)))
    {}
    
    void operator()()
    {
        storage_->call();
    }
private:
    std::unique_ptr<StorageProto> storage_;
};
}}}}
