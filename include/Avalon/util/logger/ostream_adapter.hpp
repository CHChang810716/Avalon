
#pragma once
#include <iostream>
#include <Avalon/util/fwd.hpp>
#include <memory>
#include <Avalon/util/core.hpp>
#include <Avalon/const_string.hpp>
#include <fstream>
#include <Avalon/util/fwd.hpp>
namespace avalon{ namespace util{ namespace logger{
// TODO wchar support
template<class OSTREAM_PTR>
class OstreamAdapter
{
public:
    template<class POUT>
    constexpr OstreamAdapter( const ConstString& tag, POUT&& p_out )
    : p_out_ ( FWD(p_out)       )
    , tag_   ( tag              )
    {}
    auto& get_ostream()
    {
        return *p_out_;
    }
private:
    OSTREAM_PTR p_out_;
    ConstString tag_;

template<class OS_PTR, class T>
friend std::ostream& operator<< ( OstreamAdapter<OS_PTR>& loa, T&& o );
};

constexpr auto make_adapter( const ConstString& tag, std::ostream& out )
{
    return OstreamAdapter<std::ostream*>( tag, &out );
}
template<class OSTREAM, class... ARGS>
constexpr auto make(const ConstString& tag, ARGS&&... args )
{
    return OstreamAdapter<
        std::unique_ptr<OSTREAM>
    >( tag, mkuniq(new OSTREAM(args...)));
}
template<class CHAR>
constexpr auto make_ofstream( const ConstString& tag, const CHAR* fname )
{
    return make<std::ofstream>( tag, fname );
}


template<class OS_PTR, class T>
std::ostream& operator<< ( OstreamAdapter<OS_PTR>& loa, T&& o )
{
    // render output here
    return loa.get_ostream() << '[' << loa.tag_ << ']'<< o;
}

}}}