#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <cstdint>
#include <FileBuffer.hpp>
#include "../ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp"

class Processor {
    public:
        Processor();
        ~Processor();

        void executeNextInstruction();
        void loadProgramIntoMemory(const FileBuffer& program);

    private:
        // Main registers (8 bits). Register a is an accumulator, and the other six registers
        // can be used as individual 8-bit general purpose registers or as three 16 bit register pairs
        // BC, DE, and HL.
        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
        uint8_t e;
        uint8_t h;
        uint8_t l;

        // These are both 16 bit registers. The stack pointer holds a memory address pointing to the
        // stack and the program counter holds a memory address pointing to the next instruction
        // to be executed.
        uint16_t stackPointer;    
        uint16_t programCounter;

        // Dynamically allocated buffer to represent the memory
        uint8_t* memory;

        ArithmeticAndLogicFlags flags;

        // The processor has an "Interrupt Enable" on pin 16. Two instructions, EI and DI, set this pin,
        // and this pin turns off or turns on the interrupt system, so if it is disabled,
        // interrupts will do nothing.
        bool interruptEnable;

        // Instructions take a maximum of 3 bytes
        void executeOneByteInstruction(uint8_t opcode);
        void executeTwoByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode);
        void executeThreeByteInstruction(
            uint8_t opcode,
            uint8_t firstByteFollowingOpcode,
            uint8_t secondByteFollowingOpcode
        );
};

#endif