#include <tuple>
#include <utility>
namespace avalon { namespace tuple {
// template < std::size_t... Ns , typename... Ts >
// auto tail_impl( std::index_sequence<Ns...> , std::tuple<Ts...> t )
// {
//     return  std::make_tuple( std::get<Ns+1u>(t)... );
// }
// 
// template < typename... Ts >
// auto tail( std::tuple<Ts...> t )
// {
//     return  tail_impl( std::make_index_sequence<sizeof...(Ts) - 1u>() , t );
// }
//
}}
