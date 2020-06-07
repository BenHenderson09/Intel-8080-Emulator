#include "Processor.hpp"
#include "../../config/HardwareSpecifications.hpp"

Processor::Processor() : memory{new uint8_t[HardwareSpecifications::sizeOfMemoryInBytes]} {};

Processor::~Processor(){
    // Free up memory
    delete[] memory;
}