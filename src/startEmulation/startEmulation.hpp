#ifndef START_EMULATION
#define START_EMULATION

#include <FileBuffer.hpp>
#include "../Processor/Processor.hpp"

void startEmulation(Processor& processor, const FileBuffer& program);

#endif