#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <cstdint>
#include <FileBuffer.hpp>
#include "../ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp"

class Processor {
    public:
        Processor(const FileBuffer& program);
        ~Processor();

        void beginEmulation();

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

        // Dynamically allocated buffer to represent the memory. Also store the size of the program
        // so we know when to stop iterating over memory addresses.
        uint8_t* memory;
        uint16_t sizeOfProgramInBytes;

        // Stores information about the results of arithmetic and logic instructions.
        ArithmeticAndLogicFlags flags;

        // The processor has an "Interrupt Enable" on pin 16. Two instructions, EI and DI, set this pin,
        // and this pin turns off or turns on the interrupt system, so if it is disabled,
        // interrupts will do nothing.
        bool interruptEnable;

        void executeNextInstruction();
        bool areThereInstructionsLeftToExecute();
        void loadProgramIntoMemory(const FileBuffer& program);
        void alterFlagsAfterLogicalOperation();

        // Instructions take a maximum of 3 bytes
        void executeOneByteInstruction(uint8_t opcode);
        void executeTwoByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode);
        void executeThreeByteInstruction(
            uint8_t opcode,
            uint8_t firstByteFollowingOpcode,
            uint8_t secondByteFollowingOpcode
        );

        // One byte instructions. Defined in "Processor.executeOneByteInstruction" as they only
        // act as helpers to that function. The same goes for two and three byte instructions.
        void NOP();
        void DCR(uint8_t& registerToDecrement);
        void DAD(uint8_t firstRegisterOfPair, uint8_t secondRegisterOfPair);
        void RRC();
        void INX(uint8_t& firstRegisterOfPair, uint8_t& secondRegisterOfPair);
        void LDAX(uint8_t firstRegisterOfPair, uint8_t secondRegisterOfPair);
        void MOV(uint8_t& destination, uint16_t value);
        void ANA(uint8_t registerForBitwiseAnd);
        void XRA(uint8_t registerForBitwiseXor);
        void POP(uint8_t& firstRegisterOfPair, uint8_t& secondRegisterOfPair);
        void POP_PSW();
        void PUSH(uint8_t firstRegisterOfPair, uint8_t secondRegisterOfPair);
        void PUSH_PSW();
        void RET();
        void XCHG();
        void EI();

        // Two byte instructions
        void MVI(uint8_t& destination, uint8_t data);
        void ADI(uint8_t addend);
        void ANI(uint8_t valueForBitwiseAnd);
};

#endif