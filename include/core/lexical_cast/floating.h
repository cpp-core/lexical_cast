// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <charconv>
#include "impl.h"

namespace core::lexical_cast_detail {

template<>
struct lexical_cast_impl<float> {
    float convert(std::string_view) const;
    std::string to_string(float) const;
};

template<>
struct lexical_cast_impl<double> {
    double convert(std::string_view s) const;
    std::string to_string(double) const;
};

template<>
struct lexical_cast_impl<long double> {
    long double convert(std::string_view s) const;
    std::string to_string(long double) const;
};

std::from_chars_result from_chars(const char *begin, const char *end, float& value);
std::from_chars_result from_chars(const char *begin, const char *end, double& value);
std::from_chars_result from_chars(const char *begin, const char *end, long double& value);

}; // core::lexical_cast_detail
