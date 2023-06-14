// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <string>
#include <gtest/gtest.h>
#include "core/lexical_cast/lexical_cast_tuple.h"

using namespace core;
using namespace std::string_literals;

TEST(LexicalCast, TupleIntString)
{
    for (auto str : {"123,abc", "{123,abc}"}) {
	auto tup = lexical_cast<std::tuple<int,std::string>>(str);
	EXPECT_EQ(std::get<0>(tup), 123);
	EXPECT_EQ(std::get<1>(tup), "abc");
    }
}

TEST(LexicalCast, ArrayThrow)
{
    EXPECT_THROW((lexical_cast<std::tuple<int, int>>("123,abc"s)), lexical_cast_error);
    EXPECT_THROW((lexical_cast<std::tuple<int, int>>("123"s)), lexical_cast_error);
    EXPECT_THROW((lexical_cast<std::tuple<int, int>>("123,456,789"s)), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}