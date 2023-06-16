// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/char.h"
#include "core/lexical_cast/error.h"
#include "testing.h"

inline constexpr auto NumberSamples = 64;

using test_types = core::mp::list_t<char>;

CHECK_LEXICAL();

TEST(LexicalCast, CharGenerative)
{
    UNIVERSAL_TEST(test);
    core::mp::foreach<test_types>(test, NumberSamples);
}

TEST(LexicalCast, CharConvert)
{
    check_lexical("a", 'a');
    check_lexical("b", 'b');
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
