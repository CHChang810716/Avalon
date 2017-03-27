#pragma once
#define FUNCTION_ALIAS(old_f, new_f) \
template<class...T> \
decltype(auto) new_f(T&&... o) { return old_f(std::forward<T>(o)...); }
