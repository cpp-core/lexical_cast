[![Build](https://github.com/cpp-core/lexical_cast/actions/workflows/build.yaml/badge.svg)](https://github.com/cpp-core/lexical_cast/actions/workflows/build.yaml)

Ergonomic, Type-Safe, and Extensible Conversions
================================================

# Motivation

Values often need to be converted from or to literal text,
e.g. converting between `std::vector<int>` and `std::string`. This is
a common task when reading command line arguments or configuration
files or when logging output about program state.

The `lexical_cast` library is a light-weight, header-only library that
provides for ergonomic, type-safe, and extensible conversion between
values and literal text. The `C++` builtin and standard library types
(and compositions of such) are supported out of the box. User-defined
types are easily added as first class citizens.

## Non-Goals

The `lexical` functions are designed to work with value-types and not
for the general (de)serialization of arbitrary values. There is no
support for following pointers or marking objects that is necessary
for general (de)serialization functionality.

## Other Options

The `C++` standard library has a number of facilities for performing
conversions for the builtin types that vary in their use and
extensibility.

# Tutorial

## Converting from text

### Builtin Types

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

### Standard Library Types

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

