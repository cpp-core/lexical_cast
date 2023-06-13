// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <string>
#include <tuple>
#include <vector>
#include "lexical_cast.h"
#include "util.h"

namespace core::lexical_cast_detail
{

template<class T, size_t... I>
auto create_tuple(const std::vector<std::string_view>& fields, std::index_sequence<I...>) {
    return std::make_tuple(lexical_cast<std::tuple_element_t<I, T>>(fields[I])...);
}

template<class... Ts>
struct lexical_cast_impl<std::tuple<Ts...>> {
    static std::tuple<Ts...> parse(std::string_view s) {
	using Tuple = std::tuple<Ts...>;
	constexpr auto N = sizeof...(Ts);
	
	auto [iter, end] = unwrap(s.begin(), s.end());
	std::vector<std::string_view> fields;
	size_t idx{};
	while (iter < end) {
	    if (idx >= N)
		throw lexical_cast_error(s, "too many elements for std::tuple");
	    auto delim = find_first(iter, end, ',');
	    fields.emplace_back(iter, delim);
	    iter = delim + 1;
	    ++idx;
	}
	if (idx < N)
	    throw lexical_cast_error(s, "too few elements for std::tuple");
	return create_tuple<Tuple>(fields, std::make_index_sequence<N>{});
    }
};

}; // core::lexical_cast_detail

