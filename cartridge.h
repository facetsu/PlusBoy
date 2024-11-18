#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <vector>
#include "defs.h"

class Cartridge
{
    public:
    // default constructor
    Cartridge() = default;

    // constructor to load ROM immediately
    explicit Cartridge(const std::string& filepath);

    void loadROM(const std::string& filepath) 
    {
        readROM.clear();
        std::cout << "Loading ROM: " << filepath << std::endl;

        if(!std::filesystem::exists(filepath)) 
        {
            std::cout << "File does not exist: " << filepath << std::endl;
        }

        // get our filesize and resize our vector
        auto filesize = std::filesystem::file_size(filepath);
        readROM.resize(filesize);

        // open file
        std::ifstream file(filepath, std::ios::binary);
        if(!file)
        {
            std::cout << "Failed to open file." << std::endl;
        }

        // read file
        file.read(reinterpret_cast<char*>(readROM.data()), filesize);
        file.close();

        parseHeader();
        validateBootsum();
    }

    private:
        char title[16];
        u8 romsets[48];
        u8 newCartLicensee[2];
        u8 cartType, cartSize, cartRegion, cartRamsize, cartLicensee, cartVersion, headerChecksum;
        std::vector<u8> readROM;
        static constexpr u8 bitmap[48] = 
        {
            0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
            0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
            0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
        };

        void parseHeader() 
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

        bool validateBootsum() 
        {
            std::cout << "The ROMs bootcheck sum is:                  ";
            for (int i = 0; i < 48; i++) 
            {
                cout << hex << uppercase << romsets[i] << " ";
            }
            std::cout << std::endl;

            std::cout << "The required bootsum is:                    ";
            for (int i = 0; i < 48; i++) 
            {
                std::cout << bitmap[i] << " ";
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
};