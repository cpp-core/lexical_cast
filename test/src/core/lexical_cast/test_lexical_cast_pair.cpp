// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <string>
#include <gtest/gtest.h>
#include "core/lexical_cast/pair.h"
#include "core/lexical_cast/string.h"

using namespace core;

TEST(LexicalCast, PairIntString)
{
    using Pair = std::pair<int,std::string>;
    for (auto str : {"123:abc", "{123:abc}"}) {
	auto pair = lexical_cast<Pair>(str);
	auto [i, s] = pair;
	EXPECT_EQ(i, 123);
	EXPECT_EQ(s, "abc");
	EXPECT_EQ(lexical_cast<Pair>(lexical_to_string(pair)), pair);
    }
}

TEST(LexicalCast, PairNestedPair)
{
    using InnerPair = std::pair<int,std::string>;
    using Pair = std::pair<InnerPair,float>;
    for (auto str : {"{123:abc}:1.0", "{{123:abc}:1.0}"}) {
	auto pair = lexical_cast<Pair>(str);
	auto [p, f] = pair;
	auto [i, s] = p;
	EXPECT_EQ(i, 123);
	EXPECT_EQ(s, "abc");
	EXPECT_EQ(f, 1.0);
	EXPECT_EQ(lexical_cast<Pair>(lexical_to_string(pair)), pair);
    }
}

TEST(LexicalCast, PairThrow)
{
    EXPECT_THROW((lexical_cast<std::pair<int,std::string>>("12x:abc")), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
