#pragma once
#include <type_traits>
#include <Avalon/concept/expr_validator.hpp>
#include <Avalon/concept/has_requires.hpp>

#define AVALON_EXPRS(...) -> decltype( avalon::concept::valid_expr( AVALON_VALID_EXPRS(__VA_ARGS__) ) )

#define AVALON_CONCEPT_REQUIRE_( CONCEPT_ID, ... ) \
    std::enable_if_t< avalon::concept::satisfied<CONCEPT_ID, __VA_ARGS__>, int > = 113

#define AVALON_CONCEPT_REQUIRE_NOT_( CONCEPT_ID, ... ) \
    std::enable_if_t< !avalon::concept::satisfied<CONCEPT_ID, __VA_ARGS__>, int > = 24601

namespace avalon { namespace concept { 

template<class... T>
constexpr void valid_expr( T... o );

template<class CONCEPT, class... T>
constexpr bool satisfied = avalon::concept::HasRequires<CONCEPT, void( T... )>::value;

template<bool b, std::enable_if_t<b, int> = 0>
constexpr bool is_true = b;

template<class CONCEPT, class... T>
constexpr auto requires( T... o ) AVALON_EXPRS( CONCEPT{}.requires( o... ) );

template<class CONCEPT, class... T>
using concept_requires = std::enable_if< 
      avalon::concept::satisfied< CONCEPT, T... >
    , int
>;

}}
