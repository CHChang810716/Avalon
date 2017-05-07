/**
 *Copyright (C) 2017  Chia-Hua Chang
 *
 *This file is part of Avalon.
 *
 *Avalon is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *Avalon is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with Avalon.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#pragma once
#include <iostream>
#include <Avalon/util/fwd.hpp>
#include <memory>
#include <Avalon/util/core.hpp>
#include <Avalon/const_string.hpp>
#include <fstream>
#include <Avalon/util/fwd.hpp>
#include <Avalon/type_traits/pointer.hpp>
#include <Avalon/const.hpp>
namespace avalon{ namespace util{ namespace logger{

template<class OSTREAM_PTR>
class OstreamAdapter
{
public:
    using Tag = ConstStringProto< 
        typename type_traits::DecayElementTypeT<
            OSTREAM_PTR
        >::char_type 
    >;
    template<class POUT>
    constexpr OstreamAdapter( 
          const Tag& tag
        , POUT&& p_out 
    )
    : p_out_ ( FWD(p_out)       )
    , tag_   ( tag              )
    {}
    auto& get_ostream() const
    {
        return *p_out_;
    }
    auto set_ostream(OSTREAM_PTR os_ptr)
    {
        p_out_ = std::move( os_ptr );
    }
    const auto& tag() const
    {
        return tag_;
    } 
private:
    OSTREAM_PTR p_out_;
    Tag tag_;
};
namespace detail
{
    template<class CHAR, const CVQ cvq> struct OstreamPtr{}; 
    template<class CHAR> struct OstreamPtr<CHAR, CVQ::mutable_v>
    {
        using Type = std::basic_ostream<CHAR>*;
    };
    template<class CHAR> struct OstreamPtr<CHAR, CVQ::immutable_v>
    {
        using Type = std::basic_ostream<CHAR>* const;
    };
}
template< const CVQ cvq = CVQ::immutable_v, class CHAR >
constexpr auto make_adapter( const ConstStringProto<CHAR>& tag, std::basic_ostream<CHAR>& out )
{
    return OstreamAdapter<typename detail::OstreamPtr<CHAR, cvq>::Type>( tag, &out );
}
template<class OSTREAM, class... ARGS>
constexpr auto make(const ConstStringProto<typename OSTREAM::char_type>& tag, ARGS&&... args )
{
    return OstreamAdapter<
        std::unique_ptr<OSTREAM>
    >( tag, new OSTREAM(args...));
}
template<class CHAR>
constexpr auto make_ofstream( const ConstString& tag, const CHAR* fname )
{
    return make<std::ofstream>( tag, fname );
}


template<class OS_PTR, class T>
auto& operator<< ( OstreamAdapter<OS_PTR>& loa, T&& o )
{
    // render output here
    return loa.get_ostream() << "[" << std::setw(6) << loa.tag() << "] : " << o;
}

}}}