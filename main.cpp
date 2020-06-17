#include <iostream>
#include "src/string.h"

int main() {
    /*{
        yns::String myStr1 = "123456";
        yns::String myStr2 = "123";
        yns::String myStr3 = "9";
        myStr1.replace(myStr2, myStr3);
        std::cout << myStr1;
    }

    {
        yns::String myStr1 (2,"123 456");
        yns::String myStr2 (1,"4576");
        yns::String myStr3(5, "987654");
        myStr1=myStr2+myStr1;
        std::cout << myStr1<<std::endl;
        myStr1.replace(myStr2, myStr3);
        std::cout << myStr1;
    }

     {
        yns::String myStr1 = "123123123123";
        yns::String myStr2 = "123";
        yns::String myStr3 = "321";
        myStr1.replace(myStr2, myStr3);
        std::cout << myStr1;
    }*/

    {
        yns::String myStr1 = "aaa";
        yns::String myStr2 = "a";
        yns::String myStr3 = "aaa";
        myStr1.replace(myStr2, myStr3);
        std::cout << myStr1;
    }
    return 0;
}