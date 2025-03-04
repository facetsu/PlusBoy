#pragma once
#include "../include/defs.h"
#include "../include/mmu.h"


class CPU
{
    public:
        CPU() = default;

        explicit CPU(Memory* memory);

        void run()
        {
            while (true)
            {
                fetch();
                decode();
                execute();
            }
        }
    
    u8 opcode;  // The next opcode to be decoded and run
    Memory* memory;
    void fetch();
    void decode();
    void execute();

    private:
        u8 a, b, c, d, e, f, g, h, l;  // our 8-bit registers
        u16 af, bc, de, hl;            // our 16-bit combo "registers"
        u16 sp, pc;                    // our special registers: stack pointer and program counter
        

        void setAF(u8 a, u8 f); 
        void setBC(u8 b, u8 c);
        void setDE(u8 d, u8 e);
        void setHL(u8 h, u8 l);
        u16 read16Bit();
};