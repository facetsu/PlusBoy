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

void CPU::setAF(u8 a, u8 f)
{                               
    this->af = (a << 8) | f;    
}

void CPU::setBC(u8 b, u8 c)
{
    this->bc = (b << 8) | c; 
}

void CPU::setDE(u8 d, u8 e)
{
    this->de = (d << 8) | e; 
}

void CPU::setHL(u8 h, u8 l)
{
    this->hl = (h << 8) | l; 
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

void CPU::decode()
{
    switch(opcode)
    {
        case 0x31: // LD SP, d16
            sp = read16Bit();
            break;

        case 0xAF: // XOR A,A
            a = a ^ a;
            f = 0b10000000; // sets zero flag
            break;
        
        default:
            std::cout << "Unknown opcode: " << std::hex << std::setw(2) << std::setfill('0') << (int)opcode << "\n";
            break;
    }
    
}

void CPU::execute()
{

}