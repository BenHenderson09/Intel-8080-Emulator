#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <cstdint>
#include <vector>
#include <string>
#include "../ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp"
#include "../Registers/Registers.hpp"
#include "../RegisterPair/RegisterPair.hpp"
#include "../ProcessorObserver/ProcessorObserver.hpp"
#include "../InputDevice/InputDevice.hpp"
#include "../OutputDevice/OutputDevice.hpp"

namespace Intel8080 {
    class Processor {
        public:
            Processor(const std::string& programFileLocation);
            Processor(const char* programFileLocation);
            ~Processor();

            void beginEmulation();
            void attachObserver(ProcessorObserver& observer);
            void attachInputDevice(InputDevice& device);
            void attachOutputDevice(OutputDevice& device);
            void interrupt(uint16_t address);
            bool areInterruptsEnabled();
            uint8_t readByteFromMemory(uint16_t address);

        private:
            Registers registers;
            ArithmeticAndLogicFlags flags;

            // Observers are notified when an instruction is executed,
            // and will conduct some action as a result.
            std::vector<ProcessorObserver*> observers;

            // External IO devices
            std::vector<InputDevice*> inputDevices;
            std::vector<OutputDevice*> outputDevices;

            // Dynamically allocated buffer to represent the memory. Also store the size of the program
            // so we know when to stop iterating over memory addresses.
            uint8_t* memory{new uint8_t[0xffff]};
            uint16_t sizeOfProgramInBytes;

            // The processor has an "Interrupt Enable" setting on pin 16. Two instructions, EI and DI, set this pin,
            // and this pin turns off or turns on the interrupt system, so if it is disabled,
            // interrupts will do nothing.
            bool interruptEnable{false};

            void loadProgramIntoMemory(const std::string& programFileLocation);
            void executeNextInstruction();
            void handleSleepAfterInstructionExecution(int execTimeInNanoseconds);
            double determineSleepFactorAdjustment(int cyclesRanSinceSleepFactorAdjusted);
            void notifyObserversOfInstructionExecution();
            bool areThereInstructionsLeftToExecute();
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
            void STAX(const RegisterPair& registerPair);
            void DCR(uint8_t& valueToDecrement);
            void DAA();
            void CMA();
            void RLC();
            void DAD(const RegisterPair& registerPair);
            void DCX(const RegisterPair& registerPair);
            void DCX_SP();
            void CMC();
            void RRC();
            void RAR();
            void RAL();
            void INX(RegisterPair& registerPair);
            void INR(uint8_t& valueToIncrement);
            void STC();
            void LDAX(const RegisterPair& registerPair);
            void MOV(uint8_t& destination, uint16_t value);
            void ADD(uint8_t valueToAddToAccumulator);
            void ADC(uint8_t valueToAddToAccumulator);
            void SUB(uint8_t valueToSubtractFromAccumulator);
            void ANA(uint8_t registerForBitwiseAnd);
            void XRA(uint8_t registerForBitwiseXor);
            void ORA(uint8_t valueForBitwiseOr);
            void CMP(uint8_t valueToCompare);
            void RNZ();
            void RST(int subroutineNumber);
            void POP(RegisterPair& registerPair);
            void POP_PSW();
            void PUSH(const RegisterPair& registerPair);
            void PUSH_PSW();
            void RZ();
            void RC();
            void XTHL();
            void PCHL();
            void RET();
            void RNC();
            void XCHG();
            void EI();

            // Two byte instructions
            void MVI(uint8_t& destination, uint8_t data);
            void ADI(uint8_t addend);
            void OUT(uint8_t portNumber);
            void SUI(uint8_t valueToSubtractFromAccumulator);
            void IN(uint8_t portNumber);
            void SBI(uint8_t valueToSubtractFromAccumulator);
            void ANI(uint8_t valueForBitwiseAnd);
            void CPI(uint8_t dataToCompare);
            void ORI(uint8_t valueForBitwiseOr);

            // Three byte instructions
            void LXI(RegisterPair& registerPair, uint8_t firstOperand, uint8_t secondOperand);
            void LXI_SP(uint16_t address);
            void SHLD(uint16_t address);
            void LHLD(uint16_t address);
            void STA(uint16_t address);
            void LDA(uint16_t address);
            void JNZ(uint16_t address);
            void JMP(uint16_t address);
            void CNZ(uint16_t address);
            void CALL(uint16_t address);
            void JZ(uint16_t address);
            void CZ(uint16_t address);
            void JNC(uint16_t address);
            void CNC(uint16_t address);
            void JC(uint16_t address);
            void JPO(uint16_t address);
            void JM(uint16_t address);
    };
}

#endif