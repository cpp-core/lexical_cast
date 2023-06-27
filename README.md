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

