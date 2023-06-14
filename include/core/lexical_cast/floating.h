// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include "impl.h"

namespace core::lexical_cast_detail {

template<>
struct lexical_cast_impl<float> {
    static float parse(std::string_view s);
};

template<>
struct lexical_cast_impl<double> {
    static double parse(std::string_view s);
};

template<>
struct lexical_cast_impl<long double> {
    static long double parse(std::string_view s);
};

}; // core::lexical_cast_detail
