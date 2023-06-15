// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include "core/lexical_cast/char.h"
#include "core/lexical_cast/error.h"

namespace core::lexical_cast_detail {

char lexical_cast_impl<char>::convert(std::string_view input) const {
    if (input.size() == 0)
	throw lexical_cast_error(input, "char");
    return input[0];
}

std::string lexical_cast_impl<char>::to_string(char input) const {
    return {input};
}

}; // end core::lexical_cast_detail
