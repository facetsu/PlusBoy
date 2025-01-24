#pragma once

#include <string>
#include <vector>
#include "defs.h"

class Cartridge
{
    public:
    // default constructor
    Cartridge() = default;

    // constructor to load ROM immediately
    explicit Cartridge(std::string& filepath);

    void loadROM(std::string& filepath);

    private:
        char title[16];
        u8 romsets[48];
        u8 newCartLicensee[2];
        u8 cartVersion;
        std::string cartType, cartSize, cartRegion, cartRamsize, cartLicensee, headerChecksum;
        std::vector<u8> readROM;
        static constexpr u8 BITMAP[48] = 
        {
            0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
            0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
            0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
        };

        void parseHeader();
        bool validateBootsum();
        void printDetails();
};