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

    Processor::Processor(const char* programFilePath){
        loadProgramIntoMemory(std::string{programFilePath});
    }

    Processor::~Processor(){
        delete[] memory;
    }

    void Processor::beginEmulation(){
        while (areThereInstructionsLeftToExecute()){
            int execTimeInNanoseconds {static_cast<int>(
                timeToRunInNanoseconds(
                    std::bind(&Intel8080::Processor::executeNextInstruction, this)
                )
            )};

            // Allows the emulator to run at the 8080 clock speed
            handleSleepAfterInstructionExecution(execTimeInNanoseconds);
        }
    }

    void Processor::handleSleepAfterInstructionExecution(int execTimeInNanoseconds){
        static double nanosecondsPerCycle{1e9 / ProcessorConstants::clockSpeedInHertz};
        static double sleepFactor{1};
        static auto timeWhenSleepFactorAdjusted{std::chrono::steady_clock::now()};
        static int cyclesRanSinceSleepFactorAdjusted{0};
        static int totalExecTimeInNanoseconds{0};
        static int totalDesiredExecTimeInNanoseconds{0};

        int cyclesUsedByOpcode{findNumberOfCyclesUsedByOpcode(memory[registers.programCounter])};

        cyclesRanSinceSleepFactorAdjusted += cyclesUsedByOpcode;
        totalExecTimeInNanoseconds += execTimeInNanoseconds;
        totalDesiredExecTimeInNanoseconds +=
            static_cast<int>(cyclesUsedByOpcode * nanosecondsPerCycle);

        if (totalDesiredExecTimeInNanoseconds - totalExecTimeInNanoseconds >= 1e4){
            std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<int>(1e4)));

            totalExecTimeInNanoseconds += 1e4 * sleepFactor;
        }

        sleepFactor += determineSleepFactorAdjustment(cyclesRanSinceSleepFactorAdjusted);
        cyclesRanSinceSleepFactorAdjusted = 0;
    }

    double Processor::determineSleepFactorAdjustment(int cyclesRanSinceSleepFactorAdjusted){
        static auto timeWhenSleepFactorAdjusted{std::chrono::steady_clock::now()};

        int delayBetweenAdjustmentsInNanoseconds{static_cast<int>(1e7)};
        int desiredCyclesPerAdjustment {static_cast<int>(
            ProcessorConstants::clockSpeedInHertz *
            (delayBetweenAdjustmentsInNanoseconds / 1e9)
        )};

        int nanosecondsElapsedSincePreviousAdjustment {static_cast<int>(
            (std::chrono::steady_clock::now() - timeWhenSleepFactorAdjusted).count()
        )};

        bool hasTheSpecifiedDelayElapsed {
            nanosecondsElapsedSincePreviousAdjustment >= delayBetweenAdjustmentsInNanoseconds
        };

        if (hasTheSpecifiedDelayElapsed){
            // Positive means we're running to slowly, negative means too fast.
            int cyclesAwayFromDesiredClockSpeed =
                desiredCyclesPerAdjustment - cyclesRanSinceSleepFactorAdjusted;

            timeWhenSleepFactorAdjusted = std::chrono::steady_clock::now();

            // The sleep factor will be increased or decreased by the percentage inaccuracy,
            // which will slow down or speed up the execution proportional to how close we are 
            // to the desired clock speed.
            return static_cast<double>(cyclesAwayFromDesiredClockSpeed) /
                desiredCyclesPerAdjustment;
        }

        return 0;
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
        uint8_t opcode{memory[registers.programCounter]};
        uint8_t firstByteFollowingOpcode{memory[registers.programCounter + 1]};
        uint8_t secondByteFollowingOpcode{memory[registers.programCounter + 2]};

        switch(findNumberOfBytesUsedByOpcode(opcode)){
            case 1: executeOneByteInstruction(opcode); break;
            case 2: executeTwoByteInstruction(opcode, firstByteFollowingOpcode); break;
            case 3: executeThreeByteInstruction(
                    opcode,
                    firstByteFollowingOpcode,
                    secondByteFollowingOpcode
                ); break;
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
        flags.parity = isThereAnEvenCountOfOnes(registers.a);
        flags.carry = 0;
        flags.auxiliaryCarry = 0;
    }
} 