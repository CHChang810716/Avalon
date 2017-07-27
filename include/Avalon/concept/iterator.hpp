#pragma once
#include <Avalon/concept/core.hpp>
#include <Avalon/concept/static_castible.hpp>
#include <Avalon/concept/same.hpp>
#include <vector>
#include <type_traits>
namespace avalon { namespace concept { 
struct Iterator
{
    template<class T>
    auto requires( T o ) AVALON_EXPRS(
          is_true<  std::is_copy_constructible<T>::value    >
        , is_true<  std::is_copy_assignable<T>::value       >
        , is_true<  std::is_destructible<T>::value          >
        , std::swap( o, o )
        , std::declval< typename std::iterator_traits<std::decay_t<T>>::value_type >()
        , std::declval< typename std::iterator_traits<std::decay_t<T>>::difference_type >()
        , std::declval< typename std::iterator_traits<std::decay_t<T>>::reference >()
        , std::declval< typename std::iterator_traits<std::decay_t<T>>::pointer >()
        , std::declval< typename std::iterator_traits<std::decay_t<T>>::iterator_category >()
        , *o
        , requires<Same>( ++o, std::declval<T&>() )
    );
};
struct InputIterator
{
    template<class It>
    auto requires( It i, const It j = std::declval<It>() ) AVALON_EXPRS(
          requires<Iterator>( i )
        , i == i
        , (bool)( i != j )
        , requires<Same>( *i, std::declval< typename std::iterator_traits<It>::reference >() )
        , ( is_true< std::is_convertible< 
            decltype(*i), typename std::iterator_traits<It>::value_type 
        >::value > )
        , requires<Same>( 
              i.operator->()
            , std::declval< typename std::iterator_traits<It>::pointer >() 
        )
        , requires<Same>( ++i, std::declval<It&>() )
        , (void)i++
        , (is_true < 
            std::is_convertible< 
                  decltype(*i++)
                , typename std::iterator_traits<It>::value_type 
            >::value
        >)
    );
};
struct RandomAccessIterator
{
    template<class T>
    auto requires( T&& o ) AVALON_EXPRS(
         *o, o++, o--, ++o, --o
        , o + int(), o - int()
        , o += int(), o -= int()
    );

};



}}
