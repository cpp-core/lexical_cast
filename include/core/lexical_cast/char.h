// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include "impl.h"

namespace core::lexical_cast_detail {

template<>
struct lexical_cast_impl<char> {
    char convert(std::string_view) const;
    std::string to_string(char) const;
};

}; // core::lexical_cast_detail
