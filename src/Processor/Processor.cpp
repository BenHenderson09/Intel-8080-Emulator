#include <chrono>
#include <thread>
#include <cstdint>
#include <string>
#include <functional>
#include <FileBuffer/FileBuffer.hpp>
#include "Processor.hpp"
#include "../../config/ProcessorConfig.hpp"
#include "../ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp"
#include "../FindOpcodeDetail/FindOpcodeDetail.hpp"
#include "../BinaryArithmetic/BinaryArithmetic.hpp"
#include "../../config/OpcodeConfig.hpp"
#include "../ProcessorObserver/ProcessorObserver.hpp"
#include "../InputDevice/InputDevice.hpp"
#include "../timeToRunInNanoseconds/timeToRunInNanoseconds.hpp"

using steadyClock = std::chrono::steady_clock;

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
            int execTimeInNanoseconds {int(
                timeToRunInNanoseconds(
                    std::bind(&Intel8080::Processor::executeNextInstruction, this)
                )
            )};

            // Allows the emulator to run at the 8080 clock speed
            handleSleepAfterInstructionExecution(execTimeInNanoseconds);
        }
    }

    void Processor::handleSleepAfterInstructionExecution(int execTimeInNanoseconds){
        static double nanosecondsPerCycle{1e9 / ProcessorConfig::clockSpeedInHertz};
        static double sleepFactor{1};
        static auto timeWhenSleepFactorAdjusted{steadyClock::now()};
        static int cyclesRanSinceSleepFactorAdjusted{0};
        static int totalExecTimeInNanoseconds{0};
        static int totalDesiredExecTimeInNanoseconds{0};

        int cyclesUsedByOpcode{findNumberOfCyclesUsedByOpcode(memory[registers.programCounter])};

        cyclesRanSinceSleepFactorAdjusted += cyclesUsedByOpcode;
        totalExecTimeInNanoseconds += execTimeInNanoseconds;
        totalDesiredExecTimeInNanoseconds += int(cyclesUsedByOpcode * nanosecondsPerCycle);

        if (totalDesiredExecTimeInNanoseconds - totalExecTimeInNanoseconds >= 1e4){
            std::this_thread::sleep_for(std::chrono::nanoseconds(int(1e4)));

            totalExecTimeInNanoseconds += 1e4 * sleepFactor;
        }

        sleepFactor += determineSleepFactorAdjustment(cyclesRanSinceSleepFactorAdjusted);
        cyclesRanSinceSleepFactorAdjusted = 0;
    }

    double Processor::determineSleepFactorAdjustment(int cyclesRanSinceSleepFactorAdjusted){
        static auto timeWhenSleepFactorAdjusted{steadyClock::now()};

        int delayBetweenAdjustmentsInNanoseconds{int(1e7)};
        int desiredCyclesPerAdjustment {int(
            ProcessorConfig::clockSpeedInHertz *
            (delayBetweenAdjustmentsInNanoseconds / 1e9)
        )};

        int nanosecondsElapsedSincePreviousAdjustment {
            int((steadyClock::now() - timeWhenSleepFactorAdjusted).count())
        };

        bool hasTheSpecifiedDelayElapsed {
            nanosecondsElapsedSincePreviousAdjustment >= delayBetweenAdjustmentsInNanoseconds
        };

        if (hasTheSpecifiedDelayElapsed){
            // Positive means we're running to slowly, negative means too fast.
            int cyclesAwayFromDesiredClockSpeed =
                desiredCyclesPerAdjustment - cyclesRanSinceSleepFactorAdjusted;

            timeWhenSleepFactorAdjusted = steadyClock::now();

            // The sleep factor will be increased or decreased by the percentage inaccuracy,
            // which will slow down or speed up the execution proportional to how close we are 
            // to the desired steadyClock speed.
            return double(cyclesAwayFromDesiredClockSpeed) / desiredCyclesPerAdjustment;
        }

        return 0;
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
        for (ProcessorObserver* observer : observers){
            observer->notifyInstructionHasBeenExecuted();
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