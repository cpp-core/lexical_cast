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

template<typename T>
struct number_test
{
    static void apply()
    {
	auto actual_min_value = mp::extrema<T>::min();
	auto min_repr = fmt::format(fmt::runtime(mp::extrema<T>::fmt_spec()), actual_min_value);
	auto min_value = lexical_cast<T>(min_repr);
	EXPECT_EQ(min_value, actual_min_value);

	auto actual_max_value = mp::extrema<T>::max();
	auto max_repr = fmt::format(fmt::runtime(mp::extrema<T>::fmt_spec()), actual_max_value);
	auto max_value = lexical_cast<T>(max_repr);
	EXPECT_EQ(max_value, actual_max_value);
	
	EXPECT_THROW(lexical_cast<T>("abc"), lexical_cast_error);
	
	auto generator = coro::sampler<T>(actual_min_value, actual_max_value);
	for (auto value : std::move(generator) | coro::take(5))
	{
	    std::string s = fmt::format(fmt::runtime(mp::extrema<T>::fmt_spec()), value);
	    auto n = lexical_cast<T>(s);
	    EXPECT_EQ(value, n);
	    std::string s2 = fmt::format(fmt::runtime(mp::extrema<T>::fmt_spec()), n);
	    EXPECT_EQ(s, s2);
	}
    }
};

template<class T>
void hex_test() {
    auto rng = std::random_device();
    for (auto i = 0; i < 256; ++i) {
	T n{(T)rng()};
	auto s = fmt::format("0x{:x}", n);
	auto m = lexical_cast<T>(s);
	EXPECT_EQ(m, n);
    }
}

TEST(LexicalCast, Int8)
{
    number_test<std::int8_t>::apply();
    hex_test<std::int8_t>();
}

TEST(LexicalCast, Int16)
{
    number_test<std::int16_t>::apply();
    hex_test<std::int16_t>();
}

TEST(LexicalCast, Int32)
{
    number_test<std::int32_t>::apply();
    hex_test<std::int32_t>();
}

TEST(LexicalCast, Int64)
{
    number_test<std::int64_t>::apply();
    hex_test<std::int64_t>();
}

TEST(LexicalCast, Uint8)
{
    number_test<std::uint8_t>::apply();
    hex_test<std::uint8_t>();
}

TEST(LexicalCast, Uint16)
{
    number_test<std::uint16_t>::apply();
    hex_test<std::uint16_t>();
}

TEST(LexicalCast, Uint32)
{
    number_test<std::uint32_t>::apply();
    hex_test<std::uint32_t>();
}

TEST(LexicalCast, Uint64)
{
    number_test<std::uint64_t>::apply();
    hex_test<std::uint64_t>();
}

TEST(LexicalCast, Real32)
{ number_test<float>::apply(); }

TEST(LexicalCast, Real64)
{ number_test<double>::apply(); }

TEST(LexicalCast, Real128)
{ number_test<long double>::apply(); }


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
