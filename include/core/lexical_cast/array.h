// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <array>
#include "builtin.h"
#include "error.h"
#include "util.h"

namespace core::lexical_cast_detail {

template<class T, size_t N>
struct lexical_cast_impl<std::array<T, N>> {
    static std::array<T, N> parse(std::string_view s) {
	auto [iter, end] = unwrap(s.begin(), s.end());
	size_t idx{};
	std::array<T, N> arr{};
	while (iter < end) {
	    if (idx >= N)
		throw lexical_cast_error(s, "too many elements for std::array");
	    auto delim = find_first(iter, end, ',');
	    arr[idx] = lexical_cast<T>({iter, delim});
	    iter = delim + 1;
	    ++idx;
	}
	if (idx < N)
	    throw lexical_cast_error(s, "too few elements for std::array");
	return arr;
    }
};

}; // core::lexical_cast_detail

