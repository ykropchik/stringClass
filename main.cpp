#include <iostream>
#include "src/string.h"

int main() {
    yns::String myStr1 = "123456";
    yns::String myStr2 = "123";
    yns::String myStr3 = "9";
    myStr1.replace(myStr2, myStr3);
    std::cout << myStr1;
    return 0;
}