// Copyright (C) 2017, 2018, 2019, 2021, 2022, 2023 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/lexical_cast/tuple.h"
#include "core/lexical_cast/string.h"
#include "coro/stream/stream.h"
#include "core/mp/foreach.h"

using namespace core;
using namespace coro;

// inline constexpr auto NumberSamples = 4;

// using test_types = core::mp::list_t
//     <std::tuple<unsigned int,std::string>,
//      std::tuple<std::string>,
//      std::tuple<std::string, bool>>;

// TEST(LexicalCast, TupleGenerative)
// {
//     auto test = []<class T>() {
// 	for (auto s : sampler<T>() | take(NumberSamples))
// 	    EXPECT_EQ(lexical_cast<T>(lexical_to_string(s)), s);
//     };

//     core::mp::foreach<test_types>(test);
// }

TEST(LexicalCast, TupleIntString)
{
    for (auto str : {"123,abc", "{123,abc}"}) {
	auto tup = lexical_cast<std::tuple<int,std::string>>(str);
	EXPECT_EQ(std::get<0>(tup), 123);
	EXPECT_EQ(std::get<1>(tup), "abc");
	EXPECT_EQ(lexical_to_string(tup), "{123,\"abc\"}");
    }
}

TEST(LexicalCast, TupleThrow)
{
    EXPECT_THROW((lexical_cast<std::tuple<int, int>>("123,abc")), lexical_cast_error);
    EXPECT_THROW((lexical_cast<std::tuple<int, int>>("123")), lexical_cast_error);
    EXPECT_THROW((lexical_cast<std::tuple<int, int>>("123,456,789")), lexical_cast_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
