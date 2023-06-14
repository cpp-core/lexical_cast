// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <fmt/format.h>
#include "core/lexical_cast/lexical_cast_error.h"

namespace core {

lexical_cast_error::lexical_cast_error(std::string_view input, std::string_view type)
    : std::runtime_error(fmt::format("cannot parse '{:s}' as '{:s}'", input, type))
{ }

}; // end core
