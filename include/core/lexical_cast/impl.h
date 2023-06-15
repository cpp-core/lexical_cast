// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <string>
#include <string_view>
#include <iostream>
#include "core/mp/type_name.h"

namespace core {

namespace lexical_cast_detail {

template<class T>
struct lexical_cast_impl;

}; // lexical_cast_detail

template<class T>
T lexical_cast(std::string_view input) {
    return lexical_cast_detail::lexical_cast_impl<T>{}.convert(input);
}

template<class T>
std::string lexical_to_string(const T& input) {
    return lexical_cast_detail::lexical_cast_impl<T>{}.to_string(input);
}

}; // core
