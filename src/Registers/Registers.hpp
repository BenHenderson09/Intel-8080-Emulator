#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <cstdint>
#include "../RegisterPair/RegisterPair.hpp"

namespace Intel8080 {
    struct Registers {
        // Main registers (8 bits each). Register A is an accumulator,
        // and the other six registers can be used as individual 8-bit general purpose
        // registers or as three 16 bit register pairs BC, DE, and HL.
        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
        uint8_t e;
        uint8_t h;
        uint8_t l;

        // These are both 16 bit registers. The stack pointer holds a memory
        // address pointing to the stack and the program counter holds a memory
        // address pointing to the next instruction to be executed.
        uint16_t stackPointer;
        uint16_t programCounter{0};

        // Register pairs
        RegisterPair bc{b, c};
        RegisterPair de{d, e};
        RegisterPair hl{h, l};
    };
}

#endif