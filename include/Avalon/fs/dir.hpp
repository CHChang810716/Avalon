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
#include <boost/filesystem/path.hpp>
namespace avalon { namespace fs { 

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
