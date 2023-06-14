// Copyright (C) 2023 by Mark Melton
//

#include <iostream>
#include "core/lexical_cast/lexical_cast.h"
#include "core/mp/type_name.h"

using namespace core;
using std::cout, std::endl;

int main(int argc, const char *argv[]) {
    cout << mp::type_name<uint8_t>() << endl;
    cout << mp::type_name<uint16_t>() << endl;
    cout << mp::type_name<uint32_t>() << endl;
    cout << mp::type_name<uint64_t>() << endl;
    cout << endl;
    cout << mp::type_name<int8_t>() << endl;
    cout << mp::type_name<int16_t>() << endl;
    cout << mp::type_name<int32_t>() << endl;
    cout << mp::type_name<int64_t>() << endl;
    cout << endl;
    cout << mp::type_name<size_t>() << endl;
    return 0;
}
