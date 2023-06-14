// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include "core/lexical_cast/bool.h"
#include "core/lexical_cast/error.h"

namespace core::lexical_cast_detail {

bool lexical_cast_impl<bool>::parse(std::string_view input) {
    if (input == "0" or input == "f" or input == "F" or input == "false")
	return false;
    if (input == "1" or input == "t" or input == "T" or input == "true")
	return true;
    throw lexical_cast_error(input, "bool");
}

}; // end core::lexical_cast_detail
