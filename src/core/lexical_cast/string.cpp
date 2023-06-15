// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include "core/lexical_cast/string.h"
#include "core/lexical_cast/error.h"

namespace core::lexical_cast_detail {

std::string lexical_cast_impl<std::string>::convert(std::string_view input) const {
    return std::string(input);
}

std::string lexical_cast_impl<std::string>::to_string(std::string_view input) const {
    return std::string(input);
}

const char* lexical_cast_impl<const char*>::convert(std::string_view input) const {
    return input.begin();
}

std::string lexical_cast_impl<const char*>::to_string(const char *input) const {
    return {input};
}

}; // end core::lexical_cast_detail
