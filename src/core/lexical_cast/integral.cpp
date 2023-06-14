// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//


#include <charconv>
#include "core/lexical_cast/integral.h"
#include "core/lexical_cast/error.h"
#include "core/mp/traits/type.h"
#include "core/pp/map.h"

namespace core::lexical_cast_detail {

template<class T>
T parse_integral(std::string_view input)
{
    try
    {
	T value{0};
	int base{10};
	const char *start = input.begin();
	
	if ((input.size() > 1) and (input[0] == '0') and
	    ((input[1] == 'x') or input[1] == 'X')) {
	    start += 2;
	    base = 16;
	}
	
	auto r = std::from_chars(start, input.end(), value, base);
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
    { return parse_integral<T>(input); }
CORE_PP_EVAL_MAP(CODE, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long, signed char, signed short, signed int, signed long, signed long long);
#undef CODE

}; // core::lexical_casst_detail
