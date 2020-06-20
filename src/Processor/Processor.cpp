#include <cstdint>
#include <iostream>
#include <FileBuffer.hpp>
#include "Processor.hpp"
#include "../../config/HardwareSpecifications.hpp"
#include "../findNumberOfBytesUsedByOpcode/findNumberOfBytesUsedByOpcode.hpp"
#include "../BinaryArithmetic/BinaryArithmetic.hpp"

Processor::Processor(const FileBuffer& program){
    loadProgramIntoMemory(program);
};

Processor::~Processor(){
    // Free up memory
    delete[] memory;
}

void Processor::loadProgramIntoMemory(const FileBuffer& program){
    // Reserve a buffer on the heap for the memory
    memory = new uint8_t[HardwareSpecifications::sizeOfMemoryInBytes];
        
    // Set the program counter to the first address in memory
    registers.programCounter = 0;

    // Store the size of the program
    sizeOfProgramInBytes = program.getFileSizeInBytes();

    // Copy over the program contents into memory
    program.copyBufferContentsToAnotherBuffer(memory, HardwareSpecifications::sizeOfMemoryInBytes);
}

void Processor::beginEmulation(){
    long double lastInterrupt{0};
    long double currentTime{0};
    
    while (areThereInstructionsLeftToExecute()){
        executeNextInstruction();
    
        // Testing out a mock VBI interrupt
        currentTime += 0.0000003;

        if (interruptEnable && (currentTime - lastInterrupt) > (1.0/60.0)){
            
            memory[registers.stackPointer - 1] = extractByte<uint16_t>(registers.programCounter, 1);
            memory[registers.stackPointer - 2] = extractByte<uint16_t>(registers.programCounter, 0);
            registers.stackPointer -= 2;

            registers.programCounter = 16;

            lastInterrupt = currentTime;
        }
    }
}

bool Processor::areThereInstructionsLeftToExecute(){
    static int count;
    count++;

    return true;//registers.programCounter < sizeOfProgramInBytes;
}

void Processor::executeNextInstruction(){
    uint8_t opcode{memory[registers.programCounter]};
    uint8_t firstByteFollowingOpcode{memory[registers.programCounter + 1]};
    uint8_t secondByteFollowingOpcode{memory[registers.programCounter + 2]};

    static int count;
    count++;
    std::cout << std::dec << count << " | " << std::hex << " Program counter: " << registers.programCounter << " | " <<  " Opcode: " <<(int)memory[registers.programCounter] << " | " <<  " Stack pointer: " << registers.stackPointer << " | " <<  " Top of stack: " << (int)memory[registers.stackPointer] <</* " | " << (int)memory[registers.programCounter+1] << " | " << (int)memory[registers.programCounter+2] <<*/ '\n';

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
}

void Processor::alterFlagsAfterLogicalOperation(){
    flags.zero = (registers.a == 0);
    flags.sign = extractBit<uint8_t>(registers.a, 7);
    flags.parity = isThereAnEvenCountOfOnes(registers.a);
    flags.carry = 0;
    flags.auxiliaryCarry = 0;
}