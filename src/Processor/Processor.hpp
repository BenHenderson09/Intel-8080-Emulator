#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <cstdint>
#include <FileBuffer.hpp>
#include "../ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp"
#include "../Registers/Registers.hpp"
#include "../RegisterPair/RegisterPair.hpp"

class Processor {
    public:
        Processor(const FileBuffer& program);
        ~Processor();

        void beginEmulation();

        // Dynamically allocated buffer to represent the memory. Also store the size of the program
        // so we know when to stop iterating over memory addresses.
        uint8_t* memory;
        uint16_t sizeOfProgramInBytes;

    private:
        Registers registers;
        ArithmeticAndLogicFlags flags;

        // The processor has an "Interrupt Enable" on pin 16. Two instructions, EI and DI, set this pin,
        // and this pin turns off or turns on the interrupt system, so if it is disabled,
        // interrupts will do nothing.
        bool interruptEnable{true};

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
        void DCR(uint8_t& byteToDecrement);
        void DAD(const RegisterPair& registerPair);
        void RRC();
        void INX(RegisterPair& registerPair);
        void STC();
        void LDAX(const RegisterPair& registerPair);
        void MOV(uint8_t& destination, uint16_t value);
        void ANA(uint8_t registerForBitwiseAnd);
        void XRA(uint8_t registerForBitwiseXor);
        void POP(RegisterPair& registerPair);
        void POP_PSW();
        void PUSH(const RegisterPair& registerPair);
        void PUSH_PSW();
        void RZ();
        void RC();
        void RET();
        void XCHG();
        void EI();

        // Two byte instructions
        void MVI(uint8_t& destination, uint8_t data);
        void ADI(uint8_t addend);
        void ANI(uint8_t valueForBitwiseAnd);
        void CPI(uint8_t dataToCompare);

        // Three byte instructions
        void LXI(RegisterPair& registerPair, uint8_t firstOperand, uint8_t secondOperand);
        void LXI_SP(uint16_t address);
        void STA(uint16_t address);
        void LDA(uint16_t address);
        void JNZ(uint16_t address);
        void JMP(uint16_t address);
        void CALL(uint16_t address);
        void JZ(uint16_t address);
        void JC(uint16_t address);
};

#endif