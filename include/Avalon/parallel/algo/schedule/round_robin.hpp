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
#include <atomic>
#include <vector>
#include <Avalon/util/fwd.hpp>
#include <Avalon/util/core.hpp>
#include <iostream>
namespace avalon{ namespace parallel{ namespace algo{ namespace schedule {
template<class T> class RoundRobin{};

template<class T, class... R>
class RoundRobin< std::vector< T, R... > >
{
    using SeqContainer = std::vector<T, R...>;
public:
    using Item  = typename SeqContainer::value_type;
    using Idx   = typename SeqContainer::size_type;

    RoundRobin( SeqContainer& seq_container )
    : seq_container_ ( seq_container )
    , idx_(new std::atomic<Idx>( static_cast<Idx>(0) ) )
    {}
    auto& get() 
    {
        Idx idx_res;
        do
        {
            idx_res = idx_->load(std::memory_order_acquire);
        }while(!idx_->compare_exchange_weak(
              idx_res
            , next(idx_res)
            , std::memory_order_release
            , std::memory_order_relaxed
        ) );
        return seq_container_.at(idx_res);
    } 

protected:
    inline auto next(const Idx& o)
    {
        return ( o + 1 ) %  seq_container_.size();
    }
    SeqContainer& seq_container_;
    std::unique_ptr<std::atomic<Idx>> idx_;
};
template<class INT>
class RoundRobinInt
{
    inline auto next(const INT& o, const INT& m )
    {
        return ( o + 1 ) %  m;
    }
public:
    RoundRobinInt( )
    : max_id_ ( avalon::util::mkuniq( new std::atomic<INT>(0) ) )
    , id_ ( avalon::util::mkuniq( new std::atomic<INT>(0) ) )
    {}
    auto get() 
    {
        INT id_res;
        auto tmax_id_ = max_id_->load( std::memory_order_acquire );
        do
        {
            id_res = id_->load(std::memory_order_acquire);
        }
        while(!id_->compare_exchange_weak(
              id_res
            , next(id_res, tmax_id_)
            , std::memory_order_release
            , std::memory_order_relaxed
        ) );
        return id_res;
    } 
    auto set_max_id( INT n )
    {
        max_id_->store(n);
    }
    auto get_max_id() { return max_id_->load(); }
private:
    std::unique_ptr<std::atomic<INT>> max_id_ ;
    std::unique_ptr<std::atomic<INT>> id_;
};

template<class T>
auto make_round_robin(T& o)
{
    return RoundRobin<std::decay_t<T>> (o);
}

}}}}
