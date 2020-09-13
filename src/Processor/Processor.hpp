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
#include "../TimeKeeper/TimeKeeper.hpp"

namespace Intel8080 {
    class Processor {
        public:
            Processor(const std::string& programFilePath);
            ~Processor();

            void beginEmulation();
            void attachObserver(ProcessorObserver& observer);
            void attachInputDevice(InputDevice& device);
            void attachOutputDevice(OutputDevice& device);
            void interrupt(int interruptHandlerNumber);
            bool areInterruptsEnabled() const;
            uint8_t readByteFromMemory(uint16_t address) const;

        private:
            Registers registers;
            ArithmeticAndLogicFlags flags;
            TimeKeeper timeKeeper;
            std::vector<InputDevice*> inputDevices;
            std::vector<OutputDevice*> outputDevices;
            uint8_t* memory;
            uint16_t sizeOfProgramInBytes;
            bool hasInterruptBeenRequested{false};
            int requestedInterruptHandlerNumber;

            // Observers are notified when an instruction is executed,
            // and will conduct some action as a result (observer pattern).
            std::vector<ProcessorObserver*> observers;

            // The processor has an "Interrupt Enable" setting which turns on or off the interrupt
            // system. If it is disabled, interrupts will do nothing. It is false by default.
            bool interruptEnable{false};

            void loadProgramIntoMemory(const std::string& programFilePath);
            void executeNextInstructionWithSleepHandling();
            void executeNextInstruction();
            void notifyObserversOfInstructionExecution();
            void handleAnyRequestedInterrupts();
            bool areThereInstructionsLeftToExecute();
            void alterFlagsAfterLogicalOperation();
            void alterFlagsAfterMathematicalOperation(uint8_t result);
            uint8_t getNextOpcode();

            // Each execution function has its own source file for
            // readability (there are almost 256 different instructions)
            void executeOneByteInstruction();
            void executeTwoByteInstruction(uint8_t firstOperand);
            void executeThreeByteInstruction(
                uint8_t firstOperand,
                uint8_t secondOperand
            );

            // One byte instructions. Defined in "Processor.executeOneByteInstruction.cpp" as
            // they are only used by that function.
            // The same goes for two and three byte instructions.
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
            void SBB(uint8_t valueToSubtractFromAccumulatorWithCarry);
            void ANA(uint8_t registerForBitwiseAnd);
            void XRA(uint8_t registerForBitwiseXor);
            void ORA(uint8_t valueForBitwiseOr);
            void CMP(uint8_t valueToCompare);
            void RNZ();
            void RST(int interruptHandlerNumber);
            void POP(RegisterPair& registerPair);
            void POP_PSW();
            void PUSH(const RegisterPair& registerPair);
            void PUSH_PSW();
            void RZ();
            void RC();
            void RPO();
            void RPE();
            void RP();
            void RM();
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