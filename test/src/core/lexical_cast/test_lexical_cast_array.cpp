// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/array.h"
#include "core/lexical_cast/vector.h"
#include "core/lexical_cast/pair.h"
#include "core/lexical_cast/string.h"

using namespace core;

TEST(LexicalCast, ArrayInt)
{
    for (auto str : {"123,456,789", "{123,456,789}"}) {
	auto arr = lexical_cast<std::array<int, 3>>(str);
	EXPECT_EQ(arr.size(), 3);
	EXPECT_EQ(arr[0], 123);
	EXPECT_EQ(arr[1], 456);
	EXPECT_EQ(arr[2], 789);
    }
}

TEST(LexicalCast, ArrayNestedVector)
{
    for (auto str : {"{12,34},56", "{12,34},{56}", "{{12,34},56}"}) {
	auto arr = lexical_cast<std::array<std::vector<int>, 2>>(str);
	EXPECT_EQ(arr.size(), 2);
	EXPECT_EQ(arr[0], (std::vector<int>{12, 34}));
	EXPECT_EQ(arr[1], (std::vector<int>{56}));
    }
}

TEST(LexicalCast, ArrayPair)
{
    for (auto str : {"{123:abc},{456:def}", "[{123:abc},{456:def}]"}) {
	auto arr = lexical_cast<std::array<std::pair<int,std::string>, 2>>(str);
	EXPECT_EQ(arr.size(), 2);
	EXPECT_EQ(arr[0].first, 123);
	EXPECT_EQ(arr[0].second, "abc");
	EXPECT_EQ(arr[1].first, 456);
	EXPECT_EQ(arr[1].second, "def");
    }
}

TEST(LexicalCast, ArrayThrow)
{
    EXPECT_THROW((lexical_cast<std::array<int, 2>>("123,abc")), lexical_cast_error);
    EXPECT_THROW((lexical_cast<std::array<int, 2>>("123")), lexical_cast_error);
    EXPECT_THROW((lexical_cast<std::array<int, 2>>("123,456,789")), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
