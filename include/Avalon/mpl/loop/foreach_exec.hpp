#pragma once
#include <Avalon/util/mutable.hpp>
#include <tuple>
namespace avalon { namespace mpl { namespace loop {

// template<class... Args>
// struct ForeachExec
// {
//     std::tuple<Args...> args_tup;
//     
//     template<class Func>
//     decltype(auto) operator() ( Func&& func )
//     {
//         return tuple_foreach ( std::forward<Func>(func), args_tup );
//     }
// };

template< class Func, class Arg1, class... Args >
inline auto foreach_exec (Func&& f, Arg1&& a1, Args&&... a )
{
    f(std::forward<Arg1>(a1));
    foreach_exec( std::forward<Func>(f), std::forward<Args>(a)...);
}

}}}
