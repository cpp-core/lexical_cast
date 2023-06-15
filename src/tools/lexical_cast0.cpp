// Copyright (C) 2023 by Mark Melton
//

#include <iostream>
#include "core/lexical_cast/bool.h"
#include "core/lexical_cast/char.h"
#include "core/lexical_cast/floating.h"
#include "core/lexical_cast/integral.h"
#include "core/lexical_cast/string.h"

using namespace core;
using std::cout, std::endl;

int main(int argc, const char *argv[]) {
    cout << std::boolalpha;
    cout << lexical_cast<bool>("t") << endl;
    cout << lexical_to_string(true) << endl;

    cout << endl;
    cout << lexical_cast<char>("a") << endl;
    cout << lexical_to_string('a') << endl;

    cout << endl;
    cout << lexical_cast<float>("1.23") << endl;
    cout << lexical_to_string(1.23) << endl;

    cout << endl;
    cout << lexical_cast<int>("123") << endl;
    cout << lexical_to_string(123) << endl;
    return 0;
}
