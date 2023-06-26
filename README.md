[![Build](https://github.com/cpp-core/lexical_cast/actions/workflows/build.yaml/badge.svg)](https://github.com/cpp-core/lexical_cast/actions/workflows/build.yaml)

Ergonomic, Type-Safe, and Extensible Conversions
================================================

# Motivation

Values often need to be converted from or to literal text,
e.g. converting between `std::vector<int>` and `std::string`. This is
a common task when reading command line arguments or a configuration
file or when logging output about program state.

The `lexical_cast` library is a light-weight, header-only library that
provides for ergonomic, type-safe, and extensible conversion between
values and literal text. The `lexical` functions support the `C++`
composition of the builting and standard library types such as
`std::vector<int>` out of the box and are easily extensible to
user-defined types. The following snippet demonstrates converting
between `std::vector<int>` and `std::string`.

```c++
auto vec = lexical_cast<std::vector<int>>("[1, 2, 3]");
assert(vec.size() == 3 and vec[0] == 1 and vec[1] == 2 and vec[2] == 3);
assert(lexical_to_string(vec) == "[1,2,3]");
```

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
