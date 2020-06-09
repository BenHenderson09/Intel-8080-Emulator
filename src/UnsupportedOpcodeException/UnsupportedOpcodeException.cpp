#include <cstdint>
#include <iomanip>
#include <sstream>
#include "UnsupportedOpcodeException.hpp"
#include <iostream>

UnsupportedOpcodeException::UnsupportedOpcodeException(uint8_t opcode) {
    std::stringstream stream;
    stream << "The following opcode is unsupported: 0x" << std::hex << (int)opcode;

    message = stream.str();
};

const char* UnsupportedOpcodeException::what() const noexcept {
    return message.c_str();
}