#include <cstdint>
#include <chrono>
#include <cstring>
#include <thread>
#include <string>
#include <functional>
#include <FileBuffer/FileBuffer.hpp>
#include "Processor.hpp"
#include "../../constants/ProcessorConstants.hpp"
#include "../ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp"
#include "../FindOpcodeDetail/FindOpcodeDetail.hpp"
#include "../BinaryOperations/BinaryOperations.hpp"
#include "../../constants/OpcodeConstants.hpp"
#include "../ProcessorObserver/ProcessorObserver.hpp"
#include "../InputDevice/InputDevice.hpp"
#include "../timeToRunInNanoseconds/timeToRunInNanoseconds.hpp"

namespace Intel8080 {
    Processor::Processor(const std::string& programFilePath){
        loadProgramIntoMemory(programFilePath);
    }

    Processor::~Processor(){
        delete[] memory;
    }

    void Processor::beginEmulation(){
        while (areThereInstructionsLeftToExecute()){
            executeNextInstructionWithSleepHandling();
        }
    }

    void Processor::executeNextInstructionWithSleepHandling(){
        uint8_t opcode{getNextOpcode()};
        
        auto executeNextInstructionLambda {
            [this](){
                return executeNextInstruction();
            }
        };

        long execTimeInNanoseconds{timeToRunInNanoseconds(executeNextInstructionLambda)};

        // Allows the emulator to run at the 8080 clock speed
        timeKeeper.handleSleepAfterInstructionExec(execTimeInNanoseconds, opcode);
    }

    void Processor::interrupt(int interruptHandlerNumber){
        if (interruptHandlerNumber >= 0 && interruptHandlerNumber <= 7){
            // Push the program counter onto the stack
            memory[registers.stackPointer - 1] = extractByte<uint16_t>(registers.programCounter, 1);
            memory[registers.stackPointer - 2] = extractByte<uint16_t>(registers.programCounter, 0);
            registers.stackPointer -= 2;

            // Set the program counter to the address of the specified interrupt handler.
            // Each interrupt handler occupies eight bytes of memory.
            registers.programCounter = interruptHandlerNumber * 8;

            // Prevent other interrupts from interfering
            interruptEnable = false;
        }
        else {
            throw std::out_of_range("Interrupt handlers are numbered in the range 0-7.");
        }
    }

    bool Processor::areInterruptsEnabled() const {
        return interruptEnable;
    }

    uint8_t Processor::readByteFromMemory(uint16_t address) const {
        return memory[address];
    }

    void Processor::attachObserver(ProcessorObserver& observer){
        observers.push_back(&observer);
    }

    void Processor::attachInputDevice(InputDevice& device){
        inputDevices.push_back(&device);
    }

    void Processor::attachOutputDevice(OutputDevice& device){
        outputDevices.push_back(&device);
    }

    void Processor::loadProgramIntoMemory(const std::string& programFilePath){
        memory = new uint8_t[ProcessorConstants::memorySizeInBytes];
        FileBuffer program{programFilePath};

        // Store the size of the program
        sizeOfProgramInBytes = program.getFileSizeInBytes();

        // Load into memory
        program.copyBufferContentsToAnotherBuffer(memory, ProcessorConstants::memorySizeInBytes);
    }

    bool Processor::areThereInstructionsLeftToExecute(){
        return registers.programCounter < sizeOfProgramInBytes;
    }

    void Processor::executeNextInstruction(){
        uint8_t firstOperand{memory[registers.programCounter + 1]};
        uint8_t secondOperand{memory[registers.programCounter + 2]};

        switch(findNumberOfBytesUsedByOpcode(getNextOpcode())){
            case 1: executeOneByteInstruction(); break;
            case 2: executeTwoByteInstruction(firstOperand); break;
            case 3: executeThreeByteInstruction(firstOperand, secondOperand); break;
        }

        notifyObserversOfInstructionExecution();
    }

    void Processor::notifyObserversOfInstructionExecution(){
        for (ProcessorObserver* observer : observers){
            observer->notifyInstructionHasBeenExecuted();
        }
    }

    void Processor::alterFlagsAfterLogicalOperation(){
        flags.zero = registers.a == 0;
        flags.sign = extractBit<uint8_t>(registers.a, 7);
        flags.parity = isThereAnEvenNumberOfBitsSetInByte(registers.a);
        flags.carry = 0;
    }

    void Processor::alterFlagsAfterMathematicalOperation(uint8_t result){
        flags.sign = extractBit<uint8_t>(result, 7);
        flags.zero = result == 0;
        flags.parity = isThereAnEvenNumberOfBitsSetInByte(result);
    }

    uint8_t Processor::getNextOpcode(){
        return memory[registers.programCounter];
    }
} 