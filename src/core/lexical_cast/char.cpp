// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include "core/lexical_cast/char.h"
#include "core/lexical_cast/error.h"

namespace core::lexical_cast_detail {

char lexical_cast_impl<char>::parse(std::string_view input) {
    if (input.size() == 0)
	throw lexical_cast_error(input, "char");
    return input[0];
}

}; // end core::lexical_cast_detail
