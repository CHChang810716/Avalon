#pragma once

#define DISABLE_COPY(T)                             \
    T(T const &) = delete;                          \
    T& operator=(T const &t) = delete;

#define DISABLE_MOVE(T)                             \
    T(T&&) = delete;                                \
    T& operator=(T&& t) = delete;

#define DEFAULT_COPY(T)                             \
    T(T const &) = default;                         \
    T& operator=(T const &t) = default;

#define DEFAULT_MOVE(T)                             \
    T(T&&) = default;                               \
    T& operator=(T&& t) = default;

#define CREATE_DERIVED_TYPE(TYPE, PARENT_TYPE)      \
    struct TYPE : public PARENT_TYPE                \
    {                                               \
        using Base = PARENT_TYPE;                   \
        using Base::Base;                           \
        TYPE() = defalut;                           \
        DEFAULT_COPY(TYPE)                          \
        DEFAULT_MOVE(TYPE)                          \
    };

#define GETTER(return_type, getter_sig, statement ) \
    return_type getter_sig                          \
        statement                                   \
    const return_type getter_sig const              \
        statement

#define CGETTER(return_type, getter_sig, statement )    \
    const return_type getter_sig const                  \
        statement

#define T_GETTER(tpl, return_type, getter_sig, statement )  \
    tpl                                                     \
    return_type getter_sig                                  \
        statement                                           \
    tpl                                                     \
    const return_type getter_sig const                      \
        statement
#define T_CGETTER(tpl, return_type, getter_sig, statement ) \
    tpl                                                     \
    const return_type getter_sig const                      \
        statement

