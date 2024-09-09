#include "defs.h"
#include <iostream>
#include <string>


int main() {
    u8 x = u8(-50);
    std::cout << x;

    std::string tester = "BL";
    int tested = stoi(tester);
    std::cout << tested;
    return 0;
}