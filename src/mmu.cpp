#include "../include/mmu.h"

void Memory::copyROMToMemory()
{
    std::copy_n(cartridge.readROM.begin(), 0x8000, memory);
}

void Memory::printOutSomeMemory()
{
    for (int i = 0; i < 48; i++) 
    {
        cout << hex << uppercase << static_cast<int>(memory[i]) << " ";
    }
}

u8 Memory::readByte(u8 sp)
{
    return memory[sp];
}