#include "../include/cartridge.h"
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

    Cartridge cartridge(filepath, bootrompath);



    
    std::cin >> filepath;   // just to keep terminal open

    return 0;
}