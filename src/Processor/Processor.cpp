#include <cstdint>
#include <iostream>
#include <string>
#include <FileBuffer/FileBuffer.hpp>
#include "Processor.hpp"
#include "../ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp"
#include "../FindOpcodeDetail/FindOpcodeDetail.hpp"
#include "../BinaryArithmetic/BinaryArithmetic.hpp"
#include "../../config/OpcodeConfig.hpp"
#include "../ProcessorObserver/ProcessorObserver.hpp"
#include "../InputDevice/InputDevice.hpp"

namespace Intel8080 {
    Processor::Processor(const std::string& programFileLocation){
        loadProgramIntoMemory(programFileLocation);
    }

    Processor::Processor(const char* programFileLocation){
        loadProgramIntoMemory(std::string(programFileLocation));
    }

    Processor::~Processor(){
        // Free up memory
        delete[] memory;
    }

    void Processor::beginEmulation(){
        while (areThereInstructionsLeftToExecute()){
            executeNextInstruction();
        }
    }

    void Processor::interrupt(uint16_t address){
        // Push the program counter onto the stack
        memory[registers.stackPointer - 1] = extractByte<uint16_t>(registers.programCounter, 1);
        memory[registers.stackPointer - 2] = extractByte<uint16_t>(registers.programCounter, 0);
        registers.stackPointer -= 2;

        // Set the program counter to specified address to execute the interrupt
        registers.programCounter = address;

        //  Prevent other interrupts from interfering
        interruptEnable = false;
    }

    bool Processor::areInterruptsEnabled(){
        return interruptEnable;
    }

    uint8_t Processor::readByteFromMemory(uint16_t address){
        return memory[address];
    }

    void Processor::attachObserver(ProcessorObserver& observer){
        observers.push_back(&observer);
    }

    void Processor::attachInputDevice(InputDevice& inputDevice){
        inputDevices.push_back(&inputDevice);
    }

    void Processor::loadProgramIntoMemory(const std::string& programFileLocation){
        FileBuffer program{programFileLocation};

        // Store the size of the program
        sizeOfProgramInBytes = program.getFileSizeInBytes();

        // Load into memory
        program.copyBufferContentsToAnotherBuffer(memory, 0xffff);
    }

    bool Processor::areThereInstructionsLeftToExecute(){
        return registers.programCounter < sizeOfProgramInBytes;
    }

    void Processor::executeNextInstruction(){
        uint8_t opcode{memory[registers.programCounter]};
        uint8_t firstByteFollowingOpcode{memory[registers.programCounter + 1]};
        uint8_t secondByteFollowingOpcode{memory[registers.programCounter + 2]};

        switch(findNumberOfBytesUsedByOpcode(opcode)){
            case 1:
                executeOneByteInstruction(opcode);
                break;

            case 2:
                executeTwoByteInstruction(opcode, firstByteFollowingOpcode);
                break;

            case 3:
                executeThreeByteInstruction(
                    opcode,
                    firstByteFollowingOpcode,
                    secondByteFollowingOpcode
                );
                break;
        }

        notifyObserversOfInstructionExecution();
    }

    void Processor::notifyObserversOfInstructionExecution(){
        uint8_t opcode{memory[registers.programCounter]};

        for (ProcessorObserver* observer : observers){
            observer->notifyInstructionHasBeenExecuted(opcode);
        }
    }

    void Processor::alterFlagsAfterLogicalOperation(){
        flags.zero = (registers.a == 0);
        flags.sign = extractBit<uint8_t>(registers.a, 7);
        flags.parity = isThereAnEvenCountOfOnes(registers.a);
        flags.carry = 0;
        flags.auxiliaryCarry = 0;
    }
}