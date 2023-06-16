// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <string>
#include "testing.h"
#include "core/lexical_cast/set.h"
#include "core/lexical_cast/pair.h"
#include "core/lexical_cast/string.h"

inline constexpr auto NumberSamples = 64;

using test_types = core::mp::list_t
    <std::set<unsigned int>,
     std::set<int>,
     std::set<std::string>>;

template<class T>
void check_lexical(std::string_view input, const T& value) {
    auto s = lexical_cast<T>(input);
    EXPECT_EQ(s, value);
    auto r = lexical_cast<T>(lexical_to_string(s));
    EXPECT_EQ(r, s);
}

TEST(LexicalCast, SetGenerative)
{
    UNIVERSAL_TEST(test);
    core::mp::foreach<test_types>(test, NumberSamples);
}

TEST(LexicalCast, SetInt)
{
    std::set<int> value{123, 456, 789};
    for (auto input : {"123,456,789", "{123,456,789}"})
	check_lexical(input, value);
}

TEST(LexicalCast, SetString)
{
    std::set<std::string> value{""};
    for (auto input : {"{\"\"}"})
	check_lexical(input, value);
}

TEST(LexicalCast, SetNested)
{
    std::set<std::set<int>> value{{12,34},{56,78}};
    for (auto input : {"{12,34},{56,78}", "{{12,34},{56,78}}"})
	check_lexical(input, value);
}

TEST(LexicalCast, SetPair)
{
    std::set<std::pair<int,std::string>> value{{123,"abc"},{456,"def"}};
    for (auto input : {"{123:abc},{456:def}", "[{123:abc},{456:def}]"})
	check_lexical(input, value);
}

TEST(LexicalCast, SetThrow)
{
    EXPECT_THROW((lexical_cast<std::set<int>>("123,abc")), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
