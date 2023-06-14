// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <vector>
#include "builtin.h"
#include "util.h"

namespace core::lexical_cast_detail {

template<class T>
struct lexical_cast_impl<std::vector<T>> {
    static std::vector<T> parse(std::string_view s) {
	auto [iter, end] = unwrap(s.begin(), s.end());
	std::vector<T> vec;
	while (iter < end) {
	    auto delim = find_first(iter, end, ',');
	    vec.emplace_back(lexical_cast<T>({iter, delim}));
	    iter = delim + 1;
	}
	return vec;
    }
};

}; // core::lexical_cast_detail

