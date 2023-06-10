// Copyright (C) 2017, 2018, 2019, 2021, 2022 by Mark Melton
//

#include <charconv>
#include <string_view>
#include <fmt/printf.h>
#include "core/mp/traits/type.h"
#include "core/lexical_cast/lexical_cast.h"
#include "core/pp/map.h"

namespace core {

lexical_cast_error::lexical_cast_error(std::string_view input, std::string_view type)
    : std::runtime_error(fmt::sprintf("cannot parse '%s' as '%s'", input, type))
{ }

namespace lexical_cast_detail
{

std::from_chars_result from_chars(const char *begin, const char *end, float& value)
{
    value = stof(std::string(begin, end - begin));
    return { end };
}

std::from_chars_result from_chars(const char *begin, const char *end, double& value)
{
    value = stod(std::string(begin, end - begin));
    return { end };
}

std::from_chars_result from_chars(const char *begin, const char *end, long double& value)
{
    value = stold(std::string(begin, end - begin));
    return { end };
}

bool lexical_cast_impl<bool>::parse(std::string_view input)
{
    if (input == "0" or input == "f" or input == "false")
	return false;
    if (input == "1" or input == "t" or input == "true")
	return true;
    throw lexical_cast_error(input, "bool");
}

char lexical_cast_impl<char>::parse(std::string_view input)
{ return input[0]; }

std::string lexical_cast_impl<std::string>::parse(std::string_view input)
{ return std::string(input); }

const char* lexical_cast_impl<const char*>::parse(std::string_view input)
{ return input.begin(); }

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

#define CODE(T)						\
    T lexical_cast_impl<T>::parse(std::string_view input)	\
    { return parse_integral<T>(input); }
CORE_PP_EVAL_MAP(CODE, std::int8_t, std::int16_t, std::int32_t, std::int64_t,
		 std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t);
#undef CODE

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

}; // lexical_casst_detail

}; // end core
