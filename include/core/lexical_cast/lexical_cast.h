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
struct lexical_cast_impl<char>
{ static char parse(std::string_view); };

template<>
struct lexical_cast_impl<std::string>
{ static std::string parse(std::string_view); };

template<>
struct lexical_cast_impl<const char*>
{ static const char* parse(std::string_view); };

template<>
struct lexical_cast_impl<std::uint8_t>
{ static std::uint8_t parse(std::string_view s); };

template<>
struct lexical_cast_impl<std::uint16_t>
{ static std::uint16_t parse(std::string_view s); };

template<>
struct lexical_cast_impl<std::uint32_t>
{ static std::uint32_t parse(std::string_view s); };

template<>
struct lexical_cast_impl<std::uint64_t>
{ static std::uint64_t parse(std::string_view s); };

template<>
struct lexical_cast_impl<std::int8_t>
{ static std::int8_t parse(std::string_view s); };

template<>
struct lexical_cast_impl<std::int16_t>
{ static std::int16_t parse(std::string_view s); };

template<>
struct lexical_cast_impl<std::int32_t>
{ static std::int32_t parse(std::string_view s); };

template<>
struct lexical_cast_impl<std::int64_t>
{ static std::int64_t parse(std::string_view s); };

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
