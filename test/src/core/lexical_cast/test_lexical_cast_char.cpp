// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/char.h"
#include "core/lexical_cast/error.h"

using namespace core;

TEST(LexicalCast, Char)
{
    char c = lexical_cast<char>("a");
    EXPECT_EQ(c, 'a');
}

TEST(LexicalCast, CharThrow)
{
    EXPECT_THROW(lexical_cast<char>(""), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
