// Copyright (C) 2023 by Mark Melton
//

#include <iostream>
#include "core/lexical_cast/string.h"
#include "core/lexical_cast/pair.h"
#include "core/lexical_cast/map.h"

using namespace core;
using std::cout, std::endl;

int main(int argc, const char *argv[]) {
    auto text = R"({["a", 1], ["b", 2]})";
    auto m = lexical_cast<std::map<std::string,int>>(text);
    cout << lexical_to_string(m) << endl;
    return 0;
}
