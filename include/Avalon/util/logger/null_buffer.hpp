#pragma once
#include <iostream>
namespace avalon{ namespace util{ namespace logger{
class NullBuffer : public std::streambuf
{
  public:
    int overflow(int c){ return 0; }
};
NullBuffer null_buffer;
std::ostream nout(&null_buffer);
}}}
