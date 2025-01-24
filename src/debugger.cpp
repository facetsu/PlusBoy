#include "../include/cartridge.h"
#include <iostream>
#include <string>
#include <cstring>

int main() 
{
    std::string filepath;
    std::cout << "=== Cartridge Test Driver ===\n";

    // Test loading a valid ROM
    std::cout << "Please enter a rom filepath to test: " << std::endl;
    std::cin >> filepath;
        Cartridge cart(filepath);  // This will automatically:
                                     // 1. Load the ROM
                                     // 2. Parse the header
                                     // 3. Validate bootsum
                                     // 4. Print all the info
    std::cin >> filepath;
    return 0;
}