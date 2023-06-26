// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//


#include "core/lexical_cast/floating.h"
#include "core/lexical_cast/error.h"
#include "core/pp/map.h"

namespace core::lexical_cast_detail {

std::from_chars_result from_chars(const char *begin, const char *end, float& value) {
    size_t idx{};
    value = stof(std::string(begin, end - begin), &idx);
    return { begin + idx };
}

std::from_chars_result from_chars(const char *begin, const char *end, double& value) {
    size_t idx{};
    value = stod(std::string(begin, end - begin), &idx);
    return { begin + idx };
}

std::from_chars_result from_chars(const char *begin, const char *end, long double& value) {
    size_t idx{};
    value = stold(std::string(begin, end - begin), &idx);
    return { begin + idx };
}

template<class T>
T parse_floating_point(std::string_view input, std::string_view name) {
    try {
	T value = 0;
	auto r = from_chars(input.begin(), input.end(), value);
	if (r.ptr != input.end())
	    throw lexical_cast_error(input, name);
	return value;
    }
    catch (std::invalid_argument const&) {
	throw lexical_cast_error(input, name);
    }
    catch (std::out_of_range const&) {
	throw lexical_cast_error(input, name);
    }
}

#define CODE(T)								\
    T lexical_cast_impl<T>::convert(std::string_view input) const	\
    { return parse_floating_point<T>(input, #T); }			\
    std::string lexical_cast_impl<T>::to_string(T input) const		\
    { return std::to_string(input); }

CORE_PP_EVAL_MAP(CODE, float, double, long double);
#undef CODE

}; // core::lexical_cast_detail
