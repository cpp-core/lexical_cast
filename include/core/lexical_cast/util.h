// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <utility>
#include <cctype>

namespace core::lexical_cast_detail
{

inline constexpr char OpenCurly = '{';
inline constexpr char CloseCurly = '}';

inline constexpr char OpenBracket = '[';
inline constexpr char CloseBracket = ']';

inline constexpr char OpenQuote = '"';
inline constexpr char CloseQuote = '"';

template<class Iter>
Iter find_close(Iter iter, Iter end, char c) {
    while (iter < end) {
	switch (*iter) {
	case OpenCurly:
	    iter = find_close(++iter, end, CloseCurly);
	    break;

	case OpenBracket:
	    iter = find_close(++iter, end, CloseBracket);
	    break;

	default:
	    if (*iter == c)
		return iter;
	}
	++iter;
    }
    return iter;
}

template<class Iter>
Iter find_first(Iter iter, Iter end, char c) {
    while (iter < end) {
	switch (*iter) {
	case OpenCurly:
	    iter = find_close(++iter, end, CloseCurly);
	    break;

	case OpenBracket:
	    iter = find_close(++iter, end, CloseBracket);
	    break;

	default:
	    if (*iter == c)
		return iter;
	}
	++iter;
    }
    return iter;
}

template<class Iter>
bool matching_delims(Iter iter, Iter end) {
    if (*iter == OpenQuote and *(end - 1) == CloseQuote)
	return true;
    if (*iter == OpenCurly and end - 1 == find_close(iter + 1, end, CloseCurly))
	return true;
    if (*iter == OpenBracket and end - 1 == find_close(iter + 1, end, CloseBracket))
	return true;
    return false;
}

template<class Iter>
std::pair<Iter,Iter> unwrap(Iter iter, Iter end) {
    while (iter < end and std::isspace(*iter))
	++iter;
    while (end > iter and std::isspace(*(end - 1)))
	--end;
    if (iter < end and matching_delims(iter, end)) {
	++iter;
	--end;
    }
    return {iter, end};
}

}; // core::lexical_cast_detail

