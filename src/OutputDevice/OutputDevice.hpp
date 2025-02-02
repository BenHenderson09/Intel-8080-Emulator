#ifndef OUTPUT_DEVICE_HPP
#define OUTPUT_DEVICE_HPP

#include <cstdint>
#include <vector>
#include <initializer_list>

namespace Intel8080 {
    class OutputDevice {
        public:
            OutputDevice(const std::initializer_list<uint8_t>& outputPortNumbers);
            virtual ~OutputDevice(){}

            const std::vector<uint8_t> outputPortNumbers;

            virtual void writeByte(uint8_t portNumber, uint8_t byte) = 0;
    };
}

#endif