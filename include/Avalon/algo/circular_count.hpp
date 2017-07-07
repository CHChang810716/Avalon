#pragma once

namespace avalon{ namespace algo{

template<class T>
struct CircularCount
{
    CircularCount( const T& o )
    : limited( o )
    {}

    T next( const T& n )
    {
        return ( n + 1 ) % limited; // TODO remove 1, use trait 
    }
private:
    const T limited;
};

}}