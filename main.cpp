#include <iostream>
#include "src/string.h"

int main() {

    yns::String myStr3 = "0123";
    yns::String myStr4 = "456789";

    yns::String myStr5 = myStr3 + myStr4;
    std::cout << myStr5;
    return 0;
}