#include "../include/cpu.h"
#include <iomanip>

CPU::CPU(Memory* memory)
{
    this->memory = memory;
    sp = 0;
    pc = 0;
}

/* 
 * For the following functions, they set the values of the 16-bit registers.
 * We bitshift the first 8-bit register into the higher 8 bits
 * and then OR the result with the second register to set the lower 8 bits.
*/ 

void CPU::setAF()
{                               
    af = (a << 8) | f;    
}

void CPU::setBC()
{
    bc = (b << 8) | c; 
}

void CPU::setDE()
{
    de = (d << 8) | e; 
}

void CPU::setHL()
{
    hl = (h << 8) | l; 
}

u8 CPU::read8Bit()
{
    u8 toReturn = memory->readByte(pc);
    pc++;
    return toReturn;
}

u16 CPU::read16Bit()
{
    u8 low = memory->readByte(pc);
    pc++;
    u8 high = memory->readByte(pc);
    pc++;

    u16 address = (high << 8) | low; // bitwise shifts to align into a single 16 bit valuer
    return address;
}

void CPU::fetch()
{
    opcode = memory->readByte(pc);
    pc++;
}