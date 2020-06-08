#include <FileBuffer.hpp>
#include "startEmulation.hpp"
#include "../Processor/Processor.hpp"

void startEmulation(Processor& processor, const FileBuffer& program){
    processor.loadProgramIntoMemory(program);
    processor.executeNextInstruction();
}