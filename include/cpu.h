#pragma once
#include "../include/defs.h"
#include "../include/mmu.h"


class CPU
{
    public:
        CPU() = default;

        explicit CPU(Memory* memory);

        // our constant loop for emulation
        void run()
        {
            while (true)
            {
                fetch();
                interpret();
            }
        }
    
        u8 opcode;  // The next opcode to be decoded and run
        Memory* memory;
        void fetch();
        void interpret();

    private:
        u8 a, b, c, d, e, f, g, h, l;  // our 8-bit registers
        u16 af, bc, de, hl;            // our 16-bit combo "registers"
        u16 sp, pc;                    // our special registers: stack pointer and program counter
        

        void setAF(); 
        void setBC();
        void setDE();
        void setHL();
        u8 read8Bit();
        u16 read16Bit();
};