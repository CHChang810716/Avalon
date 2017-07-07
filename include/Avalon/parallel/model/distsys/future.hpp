#pragma once
#include <future>
#include <Avalon/parallel/model/distsys/helper/get_id.hpp>
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
    decltype(auto) sync()
    {
        auto itr = service_.core_map_queue_.find( 
            helper::get_id( avalon::mpl::Type<Core>() ) 
        );
        if ( itr != service_.core_map_queue_.end() )
        {
            auto& queue = itr->second;
            while( Base::wait_for ( std::chrono::milliseconds(0) ) != std::future_status::ready )
            {
                SERVICE::run_task( *queue );
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
