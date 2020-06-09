#ifndef UNSUPPORTED_OPERATION_EXCEPTION_HPP
#define UNSUPPORTED_OPERATION_EXCEPTION_HPP

#include <stdexcept>
#include <cstdint>

class UnsupportedOpcodeException : public std::exception {
    public:
        UnsupportedOpcodeException(uint8_t opcode);

        const char* what() const noexcept override;

    private:
        std::string message;
};

#endif