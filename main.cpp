#include <iostream>
#include "src/string.h"

int main() {

    std::string str = "My first string";
    yns::String myStr = str;
    std::cout << myStr;
    return 0;
}