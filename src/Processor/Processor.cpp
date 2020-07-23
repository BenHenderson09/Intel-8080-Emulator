#include <cstdint>
#include <string>
#include <FileBuffer/FileBuffer.hpp>
#include "Processor.hpp"
#include "../ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp"
#include "../FindOpcodeDetail/FindOpcodeDetail.hpp"
#include "../BinaryArithmetic/BinaryArithmetic.hpp"
#include "../../config/OpcodeConfig.hpp"
#include "../ProcessorObserver/ProcessorObserver.hpp"
#include "../InputDevice/InputDevice.hpp"

#include <chrono>
#include <iostream>
#include <unistd.h>
#include <thread>

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
        auto timeWhenSleepFactorAdjusted{std::chrono::steady_clock::now()};
        int cyclesRanSinceSleepFactorAdjusted{0};
        double secondsPerCycle{1.0 / 3000000};
        int totalExecutionTimeElapsedInNanoseconds{0};
        int totalExecutionTimeMeantToBeElapsedInNanoseconds{0};
        double sleepFactor{1};

        while (areThereInstructionsLeftToExecute()) {
            int cyclesUsedByOpcode{
                findNumberOfCyclesUsedByOpcode(memory[registers.programCounter])
            };

            cyclesRanSinceSleepFactorAdjusted += cyclesUsedByOpcode;

            auto timeBeforeExecution{std::chrono::steady_clock::now()};
            executeNextInstruction();
            auto timeAfterExecution{std::chrono::steady_clock::now()};

            int executionTimeInNanoseconds{int((timeAfterExecution-timeBeforeExecution).count())};
            int desiredExecutionTimeInNanoseconds{
                int(cyclesUsedByOpcode * secondsPerCycle * 1000000000)
            };

            totalExecutionTimeElapsedInNanoseconds += executionTimeInNanoseconds;
            totalExecutionTimeMeantToBeElapsedInNanoseconds += desiredExecutionTimeInNanoseconds;

            if (totalExecutionTimeMeantToBeElapsedInNanoseconds - totalExecutionTimeElapsedInNanoseconds >= 10000){
                std::this_thread::sleep_for(std::chrono::nanoseconds(10000));

                totalExecutionTimeElapsedInNanoseconds += 10000 * sleepFactor;
            }

            sleepFactor += determineSleepFactorAdjustment(
                timeWhenSleepFactorAdjusted,
                cyclesRanSinceSleepFactorAdjusted
            );
        }
    }

    double Processor::determineSleepFactorAdjustment(
            std::chrono::time_point<std::chrono::steady_clock>& timeWhenSleepFactorAdjusted,
            int& cyclesRanSinceSleepFactorAdjusted){
        int delayBetweenAdjustmentsInNanoseconds{10000000};
        int numberOfCyclesAwayFromDesiredClockSpeed{0};

        int nanosecondsElapsedSincePreviousAdjustment{
            int((std::chrono::steady_clock::now() - timeWhenSleepFactorAdjusted).count())
        };

        bool hasTheSpecifiedDelayElapsed {
            nanosecondsElapsedSincePreviousAdjustment >= delayBetweenAdjustmentsInNanoseconds
        };

        if (hasTheSpecifiedDelayElapsed){
            // Positive means we're running to slowly, negative means too fast.
            numberOfCyclesAwayFromDesiredClockSpeed = 30000 - cyclesRanSinceSleepFactorAdjusted;

            timeWhenSleepFactorAdjusted = std::chrono::steady_clock::now();
            cyclesRanSinceSleepFactorAdjusted = 0;
        }

        // The sleep factor will be increased or decreased by the percentage inaccuracy,
        // which will slow down or speed up the execution proportional to how close we are 
        // to the desired clock speed.
        return numberOfCyclesAwayFromDesiredClockSpeed / 30000.0;
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

    void Processor::attachInputDevice(InputDevice& device){
        inputDevices.push_back(&device);
    }

    void Processor::attachOutputDevice(OutputDevice& device){
        outputDevices.push_back(&device);
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