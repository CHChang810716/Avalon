#pragma once
#include <type_traits>
#include <utility>
namespace avalon{ namespace mpl{
namespace detail{
template<class STEP, STEP step>
struct StepNext
{
    template<class INI, INI ini>
    constexpr static INI call = ini + step;
};

template<class BOUND, BOUND bound>
struct BoundEnd
{
    template<class INI, INI ini>
    constexpr static bool call = ini < bound;
};
}

template<class INT, INT ini, class END, class NEXT, bool b, INT... n>
struct MakeIndexForProto
{
};
template<class INT, INT ini, class END, class NEXT, INT... n>
struct MakeIndexForProto< INT, ini, END, NEXT, true, n...>
{
    constexpr static INT next = NEXT::template call<INT, ini>;
    using Result = typename MakeIndexForProto< 
              INT
            , next
            , END
            , NEXT
            , END::template call<INT, next>
            , n...
            , ini
        >::Result
    ;
};
template<class INT, INT ini, class END, class NEXT, INT... n>
struct MakeIndexForProto< INT, ini, END, NEXT, false, n...>
{
    using Result = std::integer_sequence<INT, n...>;
};
template<class INT, INT ini, class END, class NEXT>
using MakeIndexFor = typename MakeIndexForProto<INT, ini, END, NEXT, END::template call<INT, ini> >::Result;

template<std::size_t ini, std::size_t end, std::size_t step>
constexpr auto index_for 
    = MakeIndexFor<
            std::size_t
          , ini
          , detail::BoundEnd<std::size_t, end>
          , detail::StepNext<std::size_t, step>
    >{};

}}

