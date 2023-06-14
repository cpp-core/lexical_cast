// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include "impl.h"

namespace core::lexical_cast_detail {

template<>
struct lexical_cast_impl<bool> {
    static bool parse(std::string_view);
};

}; // core::lexical_cast_detail
