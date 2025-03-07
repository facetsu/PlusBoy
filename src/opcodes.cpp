#include "../include/cpu.h"
#include <iomanip>

void CPU::interpret()
{
    switch(opcode)
    {
        case 0x21: // LD HL,u16 
            l = read8Bit();
            h = read8Bit();
            setHL();
            break;

        case 0x31: // LD SP, d16
            sp = read16Bit();
            break;

        case 0x32: // LD (HL-),A - 0x32
            fetch();
            memory->memory[hl] = a;
            hl--;
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