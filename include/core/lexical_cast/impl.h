// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <string_view>

namespace core {

namespace lexical_cast_detail {

template<class T>
struct lexical_cast_impl;

}; // lexical_cast_detail

template<class T, class... Us>
T lexical_cast(std::string_view s, Us... extra) {
    return lexical_cast_detail::lexical_cast_impl<T>::parse(s, extra...);
}

}; // core
