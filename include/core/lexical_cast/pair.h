// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <utility>
#include "builtin.h"
#include "error.h"
#include "util.h"

namespace core::lexical_cast_detail {

template<class T, class U>
struct lexical_cast_impl<std::pair<T,U>> {
    static std::pair<T,U> parse(std::string_view s) {
	auto [begin, end] = unwrap(s.begin(), s.end());
	auto iter = find_first(begin, end, ':');
	if (iter >= end)
	    throw lexical_cast_error{s, "{first:second}"};

	auto first = lexical_cast<T>({begin, iter});
	auto second = lexical_cast<U>({iter + 1, end});
	return {first, second};
    }
};

}; // core::lexical_cast_detail

