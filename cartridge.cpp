#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstring>

#include "cartridge.h"

using namespace std;

Cartridge::Cartridge(std::string& filepath) 
{
    loadROM(filepath);
}

void Cartridge::loadROM(std::string& filepath) {
   bool fileLoaded = false;
   
   while (!fileLoaded) {
       readROM.clear();
       std::cout << "Loading ROM: " << filepath << std::endl << std::endl;

       if (!std::filesystem::exists(filepath)) {
           std::cout << "File does not exist: " << filepath << std::endl;
           std::cout << "Please enter a new filepath (or 'quit' to exit): ";
           std::cin >> filepath;
           if (filepath == "quit") return;
           continue;
       }

       // get our filesize and resize our vector
       auto filesize = std::filesystem::file_size(filepath);
       readROM.resize(filesize);

       // open file
       std::ifstream file(filepath, std::ios::binary);
       if (!file) {
           std::cout << "Failed to open file." << std::endl;
           std::cout << "Please enter a new filepath (or 'quit' to exit): ";
           std::cin >> filepath;
           if (filepath == "quit") return;
           continue;
       }

       // read file
       file.read(reinterpret_cast<char*>(readROM.data()), filesize);
       file.close();

       parseHeader();
       validateBootsum();
       printDetails();
       
       fileLoaded = true;
   }
}


void Cartridge::parseHeader() 
{
    // we copy 16 bytes into "title" using
    // a pointer from the start of readROM with
    // an offset of 0x0134, the start of the title.
    std::memcpy(title, readROM.data() + 0x0134, 0x10);

    // copy 48 bytes into romset
    std::memcpy(romsets, readROM.data() + 0x0104, 0x30);

    // read the cart type, size, and ram
    cartType = readROM[0x0147];
    cartSize = readROM[0x0148];
    cartRamsize = readROM[0x0149];
    cartLicensee = readROM[0x014B];
    cartRegion = readROM[0x014A];
    cartVersion = readROM[0x014C];
    if (cartLicensee == 0x33)
    {
        std::memcpy(newCartLicensee, readROM.data() + 0x0134, 0x02);
    }
}

bool Cartridge::validateBootsum() 
{
    std::cout << "The ROMs bootcheck sum is:                  ";
    for (int i = 0; i < 48; i++) 
    {
        cout << hex << uppercase << static_cast<int>(romsets[i]) << " ";
    }
    std::cout << std::endl;

    std::cout << "The required bootsum is:                    ";
    for (int i = 0; i < 48; i++) 
    {
        std::cout << static_cast<int>(bitmap[i]) << " ";
    }
    std::cout << endl;

    for(int i = 0; i < 48; i++) 
    {
        if (romsets[i] != bitmap[i]) 
        {
            std::cout << "The title hexdump does not match! Not a genuine cartridge." << std::endl << std::endl;
            return false;
        }
    }
    std::cout << endl << "The cartridge title hexdump is validated. Continuing." << std::endl << std::endl;
    return true;
}

void Cartridge::printDetails()
{
    std::cout << hex 
    << "The cartridge's type is: 0x" << static_cast<int>(cartType) << std::endl
    << "The cartridge's size is: 0x" << static_cast<int>(cartSize) << std::endl
    << "The cartridge's RAM is: 0x" << static_cast<int>(cartRamsize) << std::endl
    << "The cartridge's licensee is: 0x" << static_cast<int>(cartLicensee) << std::endl
    << "The cartridge's region is: 0x" << static_cast<int>(cartRegion) << std::endl
    << "The cartridge's version is: 0x" << static_cast<int>(cartVersion) << std::endl;
}