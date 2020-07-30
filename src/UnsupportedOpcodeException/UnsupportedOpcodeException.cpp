#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include "UnsupportedOpcodeException.hpp"

UnsupportedOpcodeException::UnsupportedOpcodeException(uint8_t opcode) :
    std::runtime_error{createErrorMessage(opcode)} {}

std::string UnsupportedOpcodeException::createErrorMessage(uint8_t opcode){
    std::stringstream stream;
    stream << "The following opcode is unsupported: 0x" << std::hex << int(opcode);

    return stream.str();
}