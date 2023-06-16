// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/bool.h"
#include "core/lexical_cast/error.h"
#include "testing.h"

inline constexpr auto NumberSamples = 16;

using test_types = core::mp::list_t<bool>;

template<class T>
void check_lexical(std::string_view input, const T& value) {
    auto s = lexical_cast<T>(input);
    EXPECT_EQ(s, value);
    auto r = lexical_cast<T>(lexical_to_string(s));
    EXPECT_EQ(r, s);
}

TEST(LexicalCast, BoolGenerative)
{
    auto test = []<class T>() {
	for (auto s : sampler<T>() | take(NumberSamples))
	    EXPECT_EQ(lexical_cast<T>(lexical_to_string(s)), s);
    };

    core::mp::foreach<test_types>(test);
}

TEST(LexicalCast, BoolConvert)
{
    for (auto str : {"0", "f", "F", "false"})
	check_lexical(str, false);

    for (auto str : {"1", "t", "T", "true"})
	check_lexical(str, true);
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
