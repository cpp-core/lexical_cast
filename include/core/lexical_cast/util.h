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
std::pair<Iter,Iter> unwrap(Iter iter, Iter end) {
    while (iter < end and std::isspace(*iter))
	++iter;
    while (end > iter and std::isspace(*(end - 1)))
	--end;
    if (iter < end) {
	if ((*iter == OpenCurly and *(end - 1) == CloseCurly) or
	    (*iter == OpenBracket and *(end - 1) == CloseBracket)) {
	    ++iter;
	    --end;
	}
    }
    return {iter, end};
}

}; // core::lexical_cast_detail

