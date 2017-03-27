#pragma once
#include <boost/filesystem/path.hpp>
namespace UCW { namespace fs { 

template<class PATH>
auto dir(PATH&& path)
{
    return boost::filesystem::path(path).parent_path().c_str();
}
template<class PATH>
auto sdir(PATH&& path)
{
    return boost::filesystem::path(path).parent_path().string<std::string>();
}

}}
