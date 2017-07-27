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
#include <initializer_list>
#include <Avalon/util/fwd.hpp>
namespace avalon { namespace mpl { 
namespace loop {
template<class F>
struct Helper
{
    Helper(F&& f)
    :f_(FWD(f))
    {}
    template<class T>
    inline int operator()(T&& o)
    {
        f_(FWD(o));
        return 0;
    }
private:
    F f_;
};
template<class F>
auto make_helper(F&& f)
{
    return Helper<F>(FWD(f));
}
template< class Func, class... Args >
auto foreach( Func&& f, Args&&... args )
{
    return (void)std::initializer_list<int>{
        make_helper(FWD(f))(FWD(args))...
    };
}

}
}}
