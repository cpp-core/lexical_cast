// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/bool.h"
#include "core/lexical_cast/error.h"

using namespace core;
using namespace std::string_literals;

TEST(LexicalCast, BoolFromString)
{
    for (auto str : {"0", "f", "F", "false"}) 
	EXPECT_FALSE(lexical_cast<bool>(str));

    for (auto str : {"1", "t", "T", "true"})
     	EXPECT_TRUE(lexical_cast<bool>(str));
}

TEST(LexicalCast, BoolToString)
{
    EXPECT_EQ(lexical_to_string(true), "t");
    EXPECT_EQ(lexical_to_string(false), "f");
}

TEST(LexicalCast, BoolFromStringThrow)
{
    EXPECT_THROW(lexical_cast<bool>(""), lexical_cast_error);
    EXPECT_THROW(lexical_cast<bool>("2"), lexical_cast_error);
    EXPECT_THROW(lexical_cast<bool>("a"), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
