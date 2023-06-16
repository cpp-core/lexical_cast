// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/array.h"
#include "core/lexical_cast/vector.h"
#include "core/lexical_cast/pair.h"
#include "core/lexical_cast/string.h"
#include "testing.h"

inline constexpr auto NumberSamples = 64;

using test_types = core::mp::list_t
    <std::array<unsigned int, 4>,
     std::array<std::string, 3>,
     std::array<std::pair<std::string,int>, 5>>;

template<class T>
void check_lexical(std::string_view input, const T& value) {
    auto s = lexical_cast<T>(input);
    EXPECT_EQ(s, value);
    auto r = lexical_cast<T>(lexical_to_string(s));
    EXPECT_EQ(r, s);
}

TEST(LexicalCast, ArrayGenerative)
{
    auto test = []<class T>() {
	for (auto s : sampler<T>() | take(NumberSamples))
	    EXPECT_EQ(lexical_cast<T>(lexical_to_string(s)), s);
    };

    core::mp::foreach<test_types>(test);
}

TEST(LexicalCast, ArrayInt)
{
    std::array<int, 3> arr{ 123, 456, 789 };
    for (auto str : {"123,456,789", "{123,456,789}"})
	check_lexical(str, arr);
}

TEST(LexicalCast, ArrayNestedVector)
{
    std::array<std::vector<int>, 2> arr{std::vector{12, 34}, {56}};
    for (auto str : {"{12,34},56", "{12,34},{56}", "{{12,34},56}"})
	check_lexical(str, arr);
}

TEST(LexicalCast, ArrayPair)
{
    std::array<std::pair<int,std::string>, 2> arr{ std::pair{123, "abc"}, std::pair{456, "def"} };
    for (auto str : {"{123:abc},{456:def}", "[{123:abc},{456:def}]"})
	check_lexical(str, arr);
}

TEST(LexicalCast, ArrayThrow)
{
    EXPECT_THROW((lexical_cast<std::array<int, 2>>("123,abc")), lexical_cast_error);
    EXPECT_THROW((lexical_cast<std::array<int, 2>>("123")), lexical_cast_error);
    EXPECT_THROW((lexical_cast<std::array<int, 2>>("123,456,789")), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
