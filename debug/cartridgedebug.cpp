#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstring>

#include "../include/cartridge.h"
#include "../include/lookups.h"


using namespace std;

Cartridge::Cartridge(std::string& filepath) 
{
    loadROM(filepath);
}

void Cartridge::loadROM(std::string& filepath) 
{
   bool fileLoaded = false;
   
   while (!fileLoaded) 
   {
       readROM.clear();
       std::cout << "Loading ROM: " << filepath << "\n" << "\n";

       if (!std::filesystem::exists(filepath)) 
       {
           std::cout << "File does not exist: " << filepath << "\n";
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
       if (!file) 
       {
           std::cout << "Failed to open file." << "\n";
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
    std::memcpy(title, readROM.data() + 0x0134, 0x0F);

    // copy 48 bytes into romset
    std::memcpy(romsets, readROM.data() + 0x0104, 0x30);

    // copy the new licensee code into an array
    std::memcpy(newCartLicensee, readROM.data() + 0x0144, 0x02);

    cartType = get_cart_type(readROM[0x0147]);
    cartSize = get_cart_size(readROM[0x0148]);
    cartRamsize = get_ram_size(readROM[0x0149]);
    cartLicensee = get_licensee_code(readROM[0x014B], newCartLicensee);
    cartRegion = get_region_code(readROM[0x014A]);
    cartVersion = readROM[0x014C];
}

bool Cartridge::validateBootsum() 
{
    std::cout << "The ROMs bootcheck sum is:                  ";
    for (int i = 0; i < 48; i++) 
    {
        cout << hex << uppercase << static_cast<int>(romsets[i]) << " ";
    }
    std::cout << "\n";

    std::cout << "The required bootsum is:                    ";
    for (int i = 0; i < 48; i++) 
    {
        std::cout << static_cast<int>(BITMAP[i]) << " ";
    }
    std::cout << endl;

    for(int i = 0; i < 48; i++) 
    {
        if (romsets[i] != BITMAP[i]) 
        {
            std::cout << "The title hexdump does not match! Not a genuine cartridge." << "\n" << "\n";
            return false;
        }
    }
    std::cout << endl << "The cartridge title hexdump is validated. Continuing." << "\n" << "\n";
    return true;
}

void Cartridge::printDetails() 
{
    std::cout << hex
    << "The cartridge's title is: " << title << "\n" 
    << "The cartridge's type is: " << cartType << "\n"
    << "The cartridge's size is: " << cartSize << "\n"
    << "The cartridge's RAM is: " << cartRamsize << "\n"
    << "The cartridge's licensee is: " << cartLicensee << "\n"
    << "The cartridge's region is: " << cartRegion << "\n"
    << "The cartridge's version is: v" << static_cast<int>(cartVersion) << "\n";
}