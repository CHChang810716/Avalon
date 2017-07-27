#pragma once
#include <Avalon/concept.hpp>
#include <utility>
namespace avalon{ namespace range{
namespace ac_ = avalon::concept;
template<class T, class E = void >
struct AutoRefStorage{};

template<class T, AVALON_CONCEPT_REQUIRE_NOT_(ac_::LvalueReference, T)>
struct AutoRefStorage
{
    T& get()
    {
        return *data_;
    }
    void set( T& d )
    {
        data_ = &d;
    }
  private:
    std::decay_t<T>* data_;
};
template<class T, AVALON_CONCEPT_REQUIRE_(ac_::LvalueReference, T)>
struct AutoRefStorage
{
};

}}
