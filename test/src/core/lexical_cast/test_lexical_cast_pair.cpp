// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <string>
#include <gtest/gtest.h>
#include "core/lexical_cast/lexical_cast_pair.h"

using namespace core;
using namespace std::string_literals;

TEST(LexicalCast, PairIntString)
{
    using Pair = std::pair<int,std::string>;
    for (auto str : {"123:abc", "{123:abc}"}) {
	auto [i, s] = lexical_cast<Pair>(str);
	EXPECT_EQ(i, 123);
	EXPECT_EQ(s, "abc");
    }
}

TEST(LexicalCast, PairNestedPair)
{
    using InnerPair = std::pair<int,std::string>;
    using Pair = std::pair<InnerPair,float>;
    for (auto str : {"{123:abc}:1.0", "{{123:abc}:1.0}"}) {
	auto [p, f] = lexical_cast<Pair>(str);
	auto [i, s] = p;
	EXPECT_EQ(i, 123);
	EXPECT_EQ(s, "abc");
	EXPECT_EQ(f, 1.0);
    }
}

TEST(LexicalCast, PairThrow)
{
    EXPECT_THROW((lexical_cast<std::pair<int,std::string>>("12x:abc"s)), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
