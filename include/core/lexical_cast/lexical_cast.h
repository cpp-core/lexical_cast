// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <cstdint>
#include <sstream>

namespace core {

struct lexical_cast_error : public std::runtime_error
{ lexical_cast_error(std::string_view input, std::string_view type); };

namespace lexical_cast_detail
{

template<class T>
struct lexical_cast_impl;

template<>
struct lexical_cast_impl<bool>
{ static bool parse(std::string_view); };

template<>
struct lexical_cast_impl<std::string>
{ static std::string parse(std::string_view); };

template<>
struct lexical_cast_impl<const char*>
{ static const char* parse(std::string_view); };

template<>
struct lexical_cast_impl<unsigned char>
{ static unsigned char parse(std::string_view); };

template<>
struct lexical_cast_impl<unsigned short>
{ static unsigned short parse(std::string_view s); };

template<>
struct lexical_cast_impl<unsigned int>
{ static unsigned int parse(std::string_view s); };

template<>
struct lexical_cast_impl<unsigned long>
{ static unsigned long parse(std::string_view s); };

template<>
struct lexical_cast_impl<unsigned long long>
{ static unsigned long long parse(std::string_view s); };

template<>
struct lexical_cast_impl<signed char>
{ static signed char parse(std::string_view); };

template<>
struct lexical_cast_impl<signed short>
{ static signed short parse(std::string_view s); };

template<>
struct lexical_cast_impl<signed int>
{ static signed int parse(std::string_view s); };

template<>
struct lexical_cast_impl<signed long>
{ static signed long parse(std::string_view s); };

template<>
struct lexical_cast_impl<signed long long>
{ static signed long long parse(std::string_view s); };

template<>
struct lexical_cast_impl<float>
{ static float parse(std::string_view s); };

template<>
struct lexical_cast_impl<double>
{ static double parse(std::string_view s); };

template<>
struct lexical_cast_impl<long double>
{ static long double parse(std::string_view s); };

}; // lexical_cast_detail

template<class T, class... Us>
T lexical_cast(std::string_view s, Us... extra)
{ return lexical_cast_detail::lexical_cast_impl<T>::parse(s, extra...); }

}; // core
