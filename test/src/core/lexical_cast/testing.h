// Copyright 2021, 2022, 2023 by Mark Melton
//

#pragma once
#include <gtest/gtest.h>
#include "coro/stream/stream.h"
#include "core/mp/foreach.h"

using namespace core;
using namespace coro;
using std::cout, std::endl, core::mp::foreach, core::mp::list_t;

#define CHECK_LEXICAL() \
    template<class T>							\
    void check_lexical(std::string_view input, const T& value) {	\
	auto s = lexical_cast<T>(input);				\
	EXPECT_EQ(s, value);						\
	auto r = lexical_cast<T>(lexical_to_string(s));			\
	EXPECT_EQ(r, s);						\
    }

#define UNIVERSAL_TEST(NAME)						\
    auto NAME = []<class T>(size_t n) {					\
	for (auto s : sampler<T>() | take(n))				\
	    EXPECT_EQ(lexical_cast<T>(lexical_to_string(s)), s);	\
    };


