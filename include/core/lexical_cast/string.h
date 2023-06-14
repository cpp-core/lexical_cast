// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <string>
#include "impl.h"

namespace core::lexical_cast_detail {

template<>
struct lexical_cast_impl<std::string> {
    static std::string parse(std::string_view);
};

template<>
struct lexical_cast_impl<const char*> {
    static const char* parse(std::string_view);
};

}; // core::lexical_cast_detail
