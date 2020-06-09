#include <cstdint>
#include <iostream>
#include <FileBuffer.hpp>
#include "Processor.hpp"
#include "../../config/HardwareSpecifications.hpp"
#include "../findNumberOfBytesUsedByOpcode/findNumberOfBytesUsedByOpcode.hpp"

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
    programCounter = 0;

    // Store the size of the program
    sizeOfProgramInBytes = program.getFileSizeInBytes();

    // Copy over the program contents into memory
    program.copyBufferContentsToAnotherBuffer(memory, HardwareSpecifications::sizeOfMemoryInBytes);
}

void Processor::beginEmulation(){
    while (areThereInstructionsLeftToExecute()){
        executeNextInstruction();
    }
}

bool Processor::areThereInstructionsLeftToExecute(){
    return programCounter < sizeOfProgramInBytes;
}

void Processor::executeNextInstruction(){
    uint8_t opcode{memory[programCounter]};
    uint8_t firstByteFollowingOpcode{memory[programCounter + 1]};
    uint8_t secondByteFollowingOpcode{memory[programCounter + 2]};

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