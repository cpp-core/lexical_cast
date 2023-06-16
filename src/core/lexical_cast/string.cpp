// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include "core/lexical_cast/string.h"
#include "core/lexical_cast/error.h"
#include "core/lexical_cast/util.h"

namespace core::lexical_cast_detail {

std::string lexical_cast_impl<std::string>::convert(std::string_view input) const {
    auto [b, e] = unwrap(input.begin(), input.end());
    return std::string(b, e);
}

std::string lexical_cast_impl<std::string>::to_string(std::string_view input) const {
    return std::string("\"") + std::string(input) + "\"";
}

const char* lexical_cast_impl<const char*>::convert(std::string_view input) const {
    return input.begin();
}

std::string lexical_cast_impl<const char*>::to_string(const char *input) const {
    return {input};
}

}; // end core::lexical_cast_detail
