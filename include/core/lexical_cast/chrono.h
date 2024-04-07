// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023, 2024 by Mark Melton
//

#pragma once
#include <chrono>

#include <core/mp/same.h>
#include <fmt/chrono.h>

#include "error.h"
#include "impl.h"
#include "integral.h"
#include "util.h"

namespace core::lexical_cast_detail {

template <class D>
    requires core::mp::is_same_template_v<D, std::chrono::duration>
struct lexical_cast_impl<D> {
    D convert(std::string_view raw_input) const {
        std::string_view input = unwrap_ws(raw_input);
        auto n = lexical_cast<int64_t>(input);
        return D{n};
    }

    std::string to_string(D duration) const { return fmt::format("{}", duration.count()); }
};

}; // namespace core::lexical_cast_detail
