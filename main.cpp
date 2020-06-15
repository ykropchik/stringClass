#include <iostream>
#include "src/string.h"

int main() {

    yns::String myStr3 = "123456";
    std::cout << myStr3 << std::endl;
    yns::String replace = "123";
    yns::String myStr4 = "987";

    //myStr3.replace(replace, myStr4);
    std::cout << myStr3.find("34");
    return 0;
}