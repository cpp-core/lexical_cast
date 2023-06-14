// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/bool.h"
#include "core/lexical_cast/error.h"

using namespace core;

TEST(LexicalCast, Bool)
{
    EXPECT_EQ(lexical_cast<bool>("0"), false);
    EXPECT_EQ(lexical_cast<bool>("f"), false);
    EXPECT_EQ(lexical_cast<bool>("F"), false);
    EXPECT_EQ(lexical_cast<bool>("false"), false);

    EXPECT_EQ(lexical_cast<bool>("1"), true);
    EXPECT_EQ(lexical_cast<bool>("t"), true);
    EXPECT_EQ(lexical_cast<bool>("T"), true);
    EXPECT_EQ(lexical_cast<bool>("true"), true);
}

TEST(LexicalCast, BoolThrow)
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
