#pragma once
#include <type_traits>
#include <Avalon/concept/expr_validator.hpp>
#include <Avalon/concept/has_requires.hpp>
#define AVALON_EXPRS_(...) decltype( avalon::concept::valid_expr( AVALON_VALID_EXPRS(__VA_ARGS__) ) )
#define AVALON_EXPRS(...) -> AVALON_EXPRS_(__VA_ARGS__)

#define AVALON_CONCEPT_REQUIRE__( CONCEPT_ID, ... ) \
    std::enable_if_t< avalon::concept::satisfied<CONCEPT_ID, __VA_ARGS__>, int >

#define AVALON_CONCEPT_REQUIRE_NOT__( CONCEPT_ID, ... ) \
    std::enable_if_t< !avalon::concept::satisfied<CONCEPT_ID, __VA_ARGS__>, int >

#define AVALON_CONCEPT_REQUIRE_( CONCEPT_ID, ... ) \
    AVALON_CONCEPT_REQUIRE__( CONCEPT_ID, __VA_ARGS__ ) = 113

#define AVALON_CONCEPT_REQUIRE_NOT_( CONCEPT_ID, ... ) \
    AVALON_CONCEPT_REQUIRE_NOT__( CONCEPT_ID, __VA_ARGS__ ) = 24601

namespace avalon { namespace concept { 

template<class... T>
constexpr int valid_expr( T... o );

template<class CONCEPT, class... T>
constexpr bool satisfied = avalon::concept::HasRequires<CONCEPT, int( T... )>::value;

template<bool b, std::enable_if_t<b, int> = 0>
constexpr bool is_true = b;

template<class CONCEPT, class... T>
constexpr auto requires( T... o ) AVALON_EXPRS( std::declval<CONCEPT>().requires( o... ) );

template<class CONCEPT, class... T>
using require = std::enable_if_t< 
      avalon::concept::satisfied< CONCEPT, T... >
    , int
>;
template<class CONCEPT, class... T>
using require_not = std::enable_if_t< 
      !avalon::concept::satisfied< CONCEPT, T... >
    , int
>;

}}
