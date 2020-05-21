#include <iostream>
#include "src/string.h"

int main() {

    std::string str = "My first string";
    yns::String myStr;
    std::cout << myStr << "\nLength = " << myStr.getLength();
    return 0;
}