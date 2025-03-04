#include "../include/cartridge.h"
#include "../include/mmu.h"
#include "../include/cpu.h"
#include <iostream>
#include <string>
#include <cstring>
#include <filesystem>

int main() 
{
    std::string filepath;
    std::string bootrompath;
    bool fileLoaded = false;

    std::cout << "Please enter a rom filepath to test: " << std::endl;
    std::cin >> filepath;

    while (!fileLoaded) 
    {
       if (!std::filesystem::exists(filepath)) 
       {
           std::cout << "File does not exist: " << filepath << "\n";
           std::cout << "Please enter a new filepath (or 'quit' to exit): ";
           std::cin >> filepath;
           if (filepath == "quit") return -1;
           continue;
       }
       fileLoaded = true;
    }

    fileLoaded = false;
    std::cout << "Please enter a bootROM filepath to test: " << std::endl;
    std::cin >> bootrompath;

    while (!fileLoaded) 
    {
       if (!std::filesystem::exists(filepath)) 
       {
           std::cout << "File does not exist: " << filepath << "\n";
           std::cout << "Please enter a new filepath (or 'quit' to exit): ";
           std::cin >> filepath;
           if (filepath == "quit") return -1;
           continue;
       }
       fileLoaded = true;
    }

    // Initialize our memory
    Memory* memorypointer = new Memory(filepath, bootrompath);

    // Initialize our CPU and system with a pointer to memory
    CPU cpu(memorypointer);
    cpu.fetch();
    std::cout << "This is the opcode it fetched: " << static_cast<int>(cpu.opcode) << std::endl;
    delete memorypointer;

    std::cin >> filepath;   // just to keep terminal open

    return 0;
}