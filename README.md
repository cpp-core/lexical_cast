[![Build](https://github.com/cpp-core/lexical_cast/actions/workflows/build.yaml/badge.svg)](https://github.com/cpp-core/lexical_cast/actions/workflows/build.yaml)

Ergonomic, Type-Safe, and Extensible Conversions
================================================

# Motivation

Values often need to be converted from or to literal text,
e.g. converting between `std::vector<int>` and `std::string`. This is
a common task when reading command line arguments or configuration
files or when logging output about program state.

The `lexical_cast` library is a light-weight, header-only library that
provides ergonomic, type-safe, and extensible conversion between
values and literal text. The `C++` builtin and standard library types
(and compositions of such) are supported out of the box. User-defined
types are easily added as first class citizens.

The library is targeted to be more robust and complete than an adhoc
solution, but simplier and more ergonomic than `C++` streams or a
full-featured (de)serialization library.

As an example, the following code snippet reads a string representing
a vector of real-valued points where each point is represented by a
pair of doubles and returns a `std::vector<std::pair<double,double>>`.

```c++
auto vec = core::lexical_cast<std::vector<std::pair<double,double>>("[(1.0,2.0), (3.0,4.0)]");
assert(vec.size() == 2);
assert(vec[0].first == 1.0 and vec[0].second == 2.0);
assert(vec[1].first == 3.0 and vec[1].second == 4.0);
```

## Non-Goals

The library is not designed to support different output formats. An
excellent library for `json` output is [nlohman/json
library](https://github.com/nlohmann/json) and for binary, [Google
protocolo buffers](https://github.com/protocolbuffers/protobuf).

The library is not designed to work with reference or pointer
types. Thus, it is not useful for the general (de)serialization of
arbitrary values. There is no support for following pointers and
marking objects that is necessary for general (de)serialization
functionality. Good general libraries for (de)serialization include
[cereal](https://github.com/USCiLab/cereal) and
[Boost::serialization](https://www.boost.org/doc/libs/1_80_0/libs/serialization/doc/index.html).

# Tutorial

The `lexical_cast` library provides the template functions
`lexical_cast` and `lexical_to_string`, both in the core namespace,
for converting text to values and values to text respectively. The
template argument for `lexical_cast` must be supplied explicitly to
indicate how the text is to be interpreted. The template argument for
`lexical_to_string` is deduced automatically.

```c++
template<class T> T lexical_cast(std::string_view text);
template<class T> std::string lexical_to_string(const T& value);
```

The implmentation for a given type can be included individually such
as including `core/lexical_cast/bool.h` for the bool type or
`core/lexcial_cast/vector.h` for the `std::vector` type. More
commonly, including `core/lexical_cast/builtin.h` will bring in the
implementations for the builtin types and `core/lexical_cast/stdlib.h`
for the standard library types. Including `core/lexical_cast/all.h`
will pull in the kitchen sink.

## Builtin Types

The builtin types are represented as text in a straightforward fashion.
- `bool`: will accept "t", "T" and "true" as `true` and "f", "F" and
  "false" as `false`.
- `char`: maps to the corresponding single character string.
- integral types: will accept the same input as `stoi`, `stol` and `stoll`.
- floating types: will accept the same input as `stof`, `stod` and `stold`.

```c++
    auto b0 = core::lexical_cast<bool>("f");
    auto b1 = core::lexical_cast<bool>("F");
    auto b2 = core::lexical_cast<bool>("false");
    assert(b0 == b1 == b2 == false);
    
    auto b3 = core::lexical_cast<bool>("t");
    auto b4 = core::lexical_cast<bool>("T");
    auto b5 = core::lexical_cast<bool>("true");
    assert(b3 == b4 == b5 == true);

    auto c = core::lexical_cast<char>("a");
    assert(c == 'a');

    auto f = core::lexical_cast<double>("12.3");
    assert(f == 12.3);

    auto i = core::lexical_cast<int>("123");
    assert(i == 123);
```

Working example: [`lexical_cast_builtin.cpp`](./src/tools/lexical_cast_builtin.cpp)

## Standard Library Types

For `std::string`, the library allows the use of double quotes `"` to
delimit the characters of the string. If there is no ambiguity,
i.e. the string does not contain whitespace, punctuation or another
grouping character, the quotes are optional. The library will always
use double quotes around a `std::string` that is output.

For all other containers, the libary uses comma `,` as the delimiter
between elements of a colleciton. The libary allows the use of square
brackets `[`,`]`, curly braces `{`,`}`, or parentheses `(`,`)` as
delimiters around a collection when interpreting text. The library
outputs square brackets for `std::array`, `std::set`, and
`std::vector`, parentheses for `std::pair` and `std::tuple`, and curly
braces for `std::map`.

Generally, whitespace is allowed between elements of a collection and
the delimiters, but no whitespace is output by the library.

```c++
    auto a = core::lexical_cast<std::array<int,3>>("[1,2,3]");
    assert(a[0] == 1 and a[1] == 2 and a[2] == 3);

    auto m = core::lexical_cast<std::map<char,int>>("{(a,1),(b,2)}");
    assert(m['a'] == 1 and m['b'] == 2);

    auto p = core::lexical_cast<std::pair<char,int>>("(a,1)");
    assert(p.first == 'a' and p.second == 1);

    auto s = core::lexical_cast<std::set<int>>("[1,2,3]");
    assert(s.size() == 3 and s.contains(1) and s.contains(2) and s.contains(3));

    auto str = core::lexical_cast<std::string>(R"("abc")");
    assert(str == "abc");

    auto t = core::lexical_cast<std::tuple<char,int,double>>("(a,1,2.0)");
    assert(t == std::make_tuple('a', 1, 2.0));

    auto v = core::lexical_cast<std::vector<int>>("[1, 2, 3]");
    assert(v.size() == 3 and v[0] == 1 and v[1] == 2 and v[2] == 3);
```

Working example: [`lexical_cast_stdlib.cpp`](./src/tools/lexical_cast_stdlib.cpp)

# Recipes

## Dictionary: `std::map` of `std::string` -> `int`

```c++
#undef NDEBUG
#include <cassert>

#include <iostream>
#include "core/lexical_cast/string.h"
#include "core/lexical_cast/map.h"

using std::cout, std::endl;

int main(int argc, const char *argv[]) {
    using Map = std::map<std::string,int>;
    
    auto text = R"({["a", 1], ["b", 2]})";
    auto m0 = core::lexical_cast<Map>(text);
    assert(core::lexical_cast<Map>(core::lexical_to_string(m0)) == m0);

    Map m1 = {{"a", 1}, {"b", 2}};
    assert(m0 == m1);
    
    return 0;
}
```

File: [`lexical_cast_dictionary.cpp`](./src/tools/lexical_cast_dictionary.cpp)

## Vector: `std::vector` of user-defined `Point` class

```c++
#undef NDEBUG
#include <cassert>

#include <iostream>
#include "core/lexical_cast/vector.h"
#include "core/lexical_cast/pair.h"

using std::cout, std::endl;

struct Point {
    double x, y;
    bool operator==(const Point&) const = default;
};

namespace core::lexical_cast_detail {

template<>
struct lexical_cast_impl<Point> {
    Point convert(std::string_view input) const {
	auto [x, y] = lexical_cast<std::pair<double,double>>(input);
	return Point{x, y};
    }

    std::string to_string(const Point& p) const {
	return lexical_to_string(std::make_pair(p.x, p.y));
    }
};

}; // lexical_cast_detail

int main(int argc, const char *argv[]) {
    using Vector = std::vector<Point>;
    
    auto text = "[(1.0,2.0), (3.0,4.0)]";
    auto v0 = core::lexical_cast<Vector>(text);
    assert(core::lexical_cast<Vector>(core::lexical_to_string(v0)) == v0);

    Vector v1 = { Point{1.0, 2.0}, Point{3.0, 4.0} };
    assert(v0 == v1);
    
    return 0;
}
```

File: [`lexical_cast_point.cpp`](./src/tools/lexical_cast_point.cpp)

