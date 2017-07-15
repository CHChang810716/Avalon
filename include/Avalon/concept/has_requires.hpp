#pragma once
#include <type_traits>
namespace avalon{ namespace concept{

template<typename, typename T>
struct HasRequires 
{
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

template<typename C, typename Ret, typename... Args>
struct HasRequires<C, Ret(Args...)> 
{
  private:
    template<typename T>
    static constexpr auto check(T*)
        -> typename std::is_same<
            decltype( std::declval<T>().requires( std::declval<Args>()... ) ), Ret
        >::type;
    
    template<typename>
    static constexpr std::false_type check(...);
    
    typedef decltype(check<C>(0)) type;
  
  public:
    static constexpr bool value = type::value;
};

}}
