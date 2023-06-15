// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/vector.h"
#include "core/lexical_cast/pair.h"
#include "core/lexical_cast/string.h"

using namespace core;

TEST(LexicalCast, VectorInt)
{
    for (auto str : {"123,456,789", "{123,456,789}"}) {
	auto vec = lexical_cast<std::vector<int>>(str);
	EXPECT_EQ(vec.size(), 3);
	EXPECT_EQ(vec[0], 123);
	EXPECT_EQ(vec[1], 456);
	EXPECT_EQ(vec[2], 789);
	EXPECT_EQ(lexical_to_string(vec), "[123,456,789]");
    }
}

TEST(LexicalCast, VectorNestedVector)
{
    for (auto str : {"{123,456},789", "{12,34},{56,78}"}) {
	auto vec = lexical_cast<std::vector<std::vector<int>>>(str);
	EXPECT_EQ(vec.size(), 2);
    }
}

TEST(LexicalCast, VectorPair)
{
    for (auto str : {"{123:abc},{456:def}", "[{123:abc},{456:def}]"}) {
	auto vec = lexical_cast<std::vector<std::pair<int,std::string>>>(str);
	EXPECT_EQ(vec.size(), 2);
	EXPECT_EQ(vec[0].first, 123);
	EXPECT_EQ(vec[0].second, "abc");
	EXPECT_EQ(vec[1].first, 456);
	EXPECT_EQ(vec[1].second, "def");
    }
}

TEST(LexicalCast, VectorThrow)
{
    EXPECT_THROW((lexical_cast<std::vector<int>>("123,abc")), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
