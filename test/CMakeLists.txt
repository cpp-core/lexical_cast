cmake_minimum_required (VERSION 3.24 FATAL_ERROR)

find_package(Threads REQUIRED)
add_stream()

set(TESTS
  lexical_cast/array
  lexical_cast/bool
  lexical_cast/char
  lexical_cast/numbers
  lexical_cast/pair
  lexical_cast/string
  lexical_cast/tuple
  lexical_cast/util
  lexical_cast/vector
  )

set(LIBRARIES
  lexical_cast
  stream::stream
  GTest::gtest
  Threads::Threads
  )

configure_tests("core" "${LIBRARIES}" ${TESTS})
