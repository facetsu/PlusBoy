#pragma once
#include "defs.h"
#include "cartridge.h"
#include <iostream>
#include <string>
#include <algorithm>

class Memory
{
    public:

        Memory() = default;

        explicit Memory(std::string& filepath, std::string& bootrompath)
        :cartridge(filepath, bootrompath)
        {
            copyROMToMemory();
            printOutSomeMemory();
        }

        Cartridge cartridge;       // initialize our cartridge, which will load our ROM
        u8 memory[0xFFFF] = {};    // initalize 64kb of memory as 0

        void copyROMToMemory();
        void printOutSomeMemory();
        u8 readByte(u8 sp);
};