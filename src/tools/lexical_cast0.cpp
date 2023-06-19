// Copyright (C) 2023 by Mark Melton
//

#include <iostream>
#include "core/lexical_cast/string.h"
#include "core/lexical_cast/vector.h"

using namespace core;
using std::cout, std::endl;

int main(int argc, const char *argv[]) {
    std::vector<int> vec = { 1, 2, 3 };
    auto str = lexical_to_string(vec);
    cout << str << endl;
    auto vec2 = lexical_cast<std::vector<int>>(str);
    cout << std::boolalpha << (vec == vec2) << endl;
    return 0;
}
