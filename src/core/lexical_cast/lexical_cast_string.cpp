// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include "core/lexical_cast/lexical_cast_string.h"
#include "core/lexical_cast/lexical_cast_error.h"

namespace core::lexical_cast_detail {

char lexical_cast_impl<char>::parse(std::string_view input) {
    if (input.size() == 0)
	throw lexical_cast_error(input, "char");
    return input[0];
}

std::string lexical_cast_impl<std::string>::parse(std::string_view input) {
    return std::string(input);
}

const char* lexical_cast_impl<const char*>::parse(std::string_view input) {
    return input.begin();
}

}; // end core::lexical_cast_detail
