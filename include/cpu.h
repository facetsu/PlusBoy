#pragma once
#include "../include/defs.h"

class CPU
{
    public:
        CPU() = default;

    private:
        u8 a, b, c, d, e, f, g, h, l;  // our 8-bit registers
        u16 af, bc, de, hl;            // our 16-bit combo "registers"
        u16 sp, pc;                    // our special registers: stack pointer and program counter

        void setAF(u8 a, u8 f); 
        void setBC(u8 b, u8 c);
        void setDE(u8 d, u8 e);
        void setHL(u8 h, u8 l);
        void executeOpcode();
        u8 fetchOpcode(u8 sp);
};