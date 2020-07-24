#ifndef UNSUPPORTED_OPCODE_EXCEPTION_HPP
#define UNSUPPORTED_OPCODE_EXCEPTION_HPP

#include <stdexcept>
#include <cstdint>

class UnsupportedOpcodeException : public std::runtime_error {
    public:
        UnsupportedOpcodeException(uint8_t opcode);

    private:
        std::string createErrorMessage(uint8_t opcode);
};

#endif