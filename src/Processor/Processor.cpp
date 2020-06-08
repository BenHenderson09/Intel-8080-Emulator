#include <cstdint>
#include <iostream>
#include <FileBuffer.hpp>
#include "Processor.hpp"
#include "../../config/HardwareSpecifications.hpp"

Processor::Processor() :
    // Reserve a buffer on the heap for the memory
    memory{new uint8_t[HardwareSpecifications::sizeOfMemoryInBytes]},
    
    // Set the program counter to the first address in memory
    programCounter{0}
    {};

Processor::~Processor(){
    // Free up memory
    delete[] memory;
}

uint16_t Processor::getAddressOfNextInstruction() const {
    return programCounter;
}

void Processor::executeOneByteInstruction(uint8_t opcode){
    std::cout << (int) opcode << '\n';
}

void Processor::executeTwoByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode){
    std::cout << firstByteFollowingOpcode << '\n';
    std::cout << (int) opcode << '\n';
}

void Processor::executeThreeByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode,
        uint8_t secondByteFollowingOpcode){
    std::cout << (int) opcode << '\n';
    std::cout << firstByteFollowingOpcode << '\n';
    std::cout << secondByteFollowingOpcode << '\n';
}

void Processor::loadProgramIntoMemory(const FileBuffer& program){
    program.copyBufferContentsToAnotherBuffer(memory, HardwareSpecifications::sizeOfMemoryInBytes);
}

uint8_t Processor::readByteFromMemory(uint16_t memoryAddress) const {
    return memory[memoryAddress];
}
