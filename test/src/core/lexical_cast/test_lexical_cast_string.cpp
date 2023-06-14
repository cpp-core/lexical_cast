// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/lexical_cast.h"
#include "core/mp/traits/extrema.h"
#include "coro/stream/stream.h"

using namespace core;
using namespace std::string_literals;

TEST(LexicalCast, String)
{
    std::string s = lexical_cast<std::string>("abc"s);
    EXPECT_EQ(s, "abc");
}

TEST(LexicalCast, Char)
{
    char c = lexical_cast<char>("a"s);
    EXPECT_EQ(c, 'a');
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
