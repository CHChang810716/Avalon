#pragma once
#include <utility>
namespace avalon { 
template<class CHAR>
class ConstStringProto
{
public:
    using value_type = CHAR;
    using size_type = std::size_t;
    constexpr ConstStringProto( const CHAR* str )
    : str_ ( str )
    {}
    constexpr size_type size() const
    {
        size_type i(0); 
        for( i = 0; str_[i] != '\0'; i ++ );
        return i;
    }
    constexpr decltype(auto) c_str() const
    {
        return str_;
    }
private:
    const CHAR* str_;
};

template<class T, class CHAR>
decltype(auto) operator<<(T&& o, const ConstStringProto<CHAR>& str )
{
    return o << str.c_str();
}
using ConstString = ConstStringProto<char>;
    
}