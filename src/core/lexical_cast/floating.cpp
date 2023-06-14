// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//


#include <charconv>
#include "core/lexical_cast/floating.h"
#include "core/lexical_cast/error.h"
#include "core/mp/traits/type.h"
#include "core/pp/map.h"

namespace core::lexical_cast_detail {

std::from_chars_result from_chars(const char *begin, const char *end, float& value) {
    value = stof(std::string(begin, end - begin));
    return { end };
}

std::from_chars_result from_chars(const char *begin, const char *end, double& value) {
    value = stod(std::string(begin, end - begin));
    return { end };
}

std::from_chars_result from_chars(const char *begin, const char *end, long double& value) {
    value = stold(std::string(begin, end - begin));
    return { end };
}

template<class T>
T parse_floating_point(std::string_view input)
{
    try
    {
	T value = 0;
	auto r = from_chars(input.begin(), input.end(), value);
	if (r.ptr != input.end())
	    throw lexical_cast_error(input, mp::type_traits<T>::name);
	return value;
    }
    catch (std::invalid_argument const&)
    {
	throw lexical_cast_error(input, mp::type_traits<T>::name);
    }
    catch (std::out_of_range const&)
    {
	throw lexical_cast_error(input, mp::type_traits<T>::name);
    }
}

#define CODE(T)							\
    T lexical_cast_impl<T>::parse(std::string_view input)	\
    { return parse_floating_point<T>(input); }
CORE_PP_EVAL_MAP(CODE, float, double, long double);
#undef CODE

}; // core::lexical_casst_detail
