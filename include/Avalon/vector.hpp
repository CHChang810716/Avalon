#pragma once
#include <vector>
namespace avalon{
template<class I, class V>
decltype(auto) forward( I i, std::vector<V>& vec )
{
    return vec.at(i);
}
template< class I, class V>
decltype(auto) forward( I i, std::vector<V>&& vec )
{
    return std::move( vec.at(i) );
}
template<class I, class V>
decltype(auto) forward( I i, const std::vector<V>& vec )
{
    V tmp = vec.at(i);
    return std::move(tmp);
}

}
