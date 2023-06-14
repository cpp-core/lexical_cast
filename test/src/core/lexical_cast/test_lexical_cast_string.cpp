// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/string.h"

using namespace core;

TEST(LexicalCast, String)
{
    std::string s = lexical_cast<std::string>("abc");
    EXPECT_EQ(s, "abc");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
