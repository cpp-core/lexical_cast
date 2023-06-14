// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include "core/lexical_cast/string.h"
#include "core/lexical_cast/error.h"

namespace core::lexical_cast_detail {

std::string lexical_cast_impl<std::string>::parse(std::string_view input) {
    return std::string(input);
}

const char* lexical_cast_impl<const char*>::parse(std::string_view input) {
    return input.begin();
}

}; // end core::lexical_cast_detail
