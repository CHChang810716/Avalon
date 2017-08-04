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
#include <future>
#include <Avalon/parallel/model/distsys/helper/get_id.hpp>
#include <Avalon/util/language.hpp>
namespace avalon {  namespace parallel { namespace model { namespace distsys{ 

template<class T>
using FutureProto = std::future<T>;

template<class T, class SERVICE>
struct Future : public FutureProto<T>
{
    using Base = FutureProto<T>;
    using Core = typename SERVICE::Core;
    Future( Base&& base, SERVICE& service )
    : Base( std::move( base ) )
    , service_ ( service )
    {}
    DEFAULT_MOVE( Future );
    DISABLE_COPY( Future );
    decltype(auto) sync()
    {
        auto itr = service_.core_map_queue_.find( 
            helper::get_id( avalon::mpl::Type<Core>() ) 
        );
        if ( itr != service_.core_map_queue_.end() )
        {
            auto& queue = std::get<0>(itr->second);
            auto& status = std::get<1>(itr->second);
            while( Base::wait_for ( std::chrono::milliseconds(0) ) != std::future_status::ready )
            {
                SERVICE::run_task( *queue, *status );
            }
        }
        else
        {
            Base::wait();
        }
        return Base::get();
    }
protected:
    void wait(){ Base::wait(); }
    SERVICE& service_;
};
template<class T, class SERVICE>
auto make_future( 
      std::future<T>&& fut
    , SERVICE& service 
)
{
    return Future<T, SERVICE>( 
          std::move( fut )
        , service 
    );
}

}}}}
