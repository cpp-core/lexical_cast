[![Build](https://github.com/cpp-core/lexical_cast/actions/workflows/build.yaml/badge.svg)](https://github.com/cpp-core/lexical_cast/actions/workflows/build.yaml)

# Ergonomic, Type-Safe, and Extensible Conversions

## Motivation

Values often need to be converted from or to literal text,
e.g. converting between `std::vector<int>` and `std::string`. This is
a common task when reading command line arguments or a configuration
file or when logging output about the program state. Consider the
following code snippet,

```c++
auto vec = lexical_cast<std::vector<int>>("[1, 2, 3]");
assert(vec.size() == 3 and vec[0] == 1 and vec[1] == 2 and vec[2] == 3);
assert(lexical_to_string(vec) == "[1,2,3]");
```

The `lexical_cast` library is a header-only library that provides the
`lexical_cast` and `lexical_to_string` template functions for
convenient, type-safe, and extensible conversions between program
values and literal text. The `lexical` functions support the `C++`
standard library types such as `std::vector` and `std::map` out of the
box and are easily extensible to user-defined types.

## Non-Goals

The `lexical` functions are designed to work with value-types,
i.e. pointers are represented by the pointed to address and not the
pointed to object. There is no support for following a graph of
objects.

The `lexical` functions are not designed for the general
(de)serialization of program values. There is no support for following
pointers or marking objects that is necessary for general
(de)serialization functionality.

## Other Options

The `C++` standard library has a number of facilities for performing
conversions for the builtin types that vary in their use and
extensibility.

## Tutorial
