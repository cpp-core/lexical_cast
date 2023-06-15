// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include "impl.h"

namespace core::lexical_cast_detail {

template<>
struct lexical_cast_impl<unsigned char> {
    unsigned char convert(std::string_view) const;
    std::string to_string(unsigned char) const;
};

template<>
struct lexical_cast_impl<unsigned short> {
    unsigned short convert(std::string_view s) const;
    std::string to_string(unsigned short) const;
};

template<>
struct lexical_cast_impl<unsigned int> {
    unsigned int convert(std::string_view s) const;
    std::string to_string(unsigned int) const;
};

template<>
struct lexical_cast_impl<unsigned long> {
    unsigned long convert(std::string_view s) const;
    std::string to_string(unsigned long) const;
};

template<>
struct lexical_cast_impl<unsigned long long> {
    unsigned long long convert(std::string_view s) const;
    std::string to_string(unsigned long long) const;
};

template<>
struct lexical_cast_impl<signed char> {
    signed char convert(std::string_view) const;
    std::string to_string(signed char) const;
};

template<>
struct lexical_cast_impl<signed short> {
    signed short convert(std::string_view s) const;
    std::string to_string(signed short) const;
};

template<>
struct lexical_cast_impl<signed int> {
    signed int convert(std::string_view s) const;
    std::string to_string(signed int) const;
};

template<>
struct lexical_cast_impl<signed long> {
    signed long convert(std::string_view s) const;
    std::string to_string(signed long) const;
};

template<>
struct lexical_cast_impl<signed long long> {
    signed long long convert(std::string_view s) const;
    std::string to_string(signed long long) const;
};

}; // core::lexical_cast_detail
