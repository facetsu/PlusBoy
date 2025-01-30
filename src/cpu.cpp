#include "../include/cpu.h"

CPU::CPU()
{

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

u8 CPU::fetchOpcode()
{

}


void CPU::executeOpcode()
{
    u8 opcode = fetchOpcode();

}