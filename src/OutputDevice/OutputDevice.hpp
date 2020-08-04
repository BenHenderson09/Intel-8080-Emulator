#ifndef OUTPUT_DEVICE_HPP
#define OUTPUT_DEVICE_HPP

#include <cstdint>
#include <vector>
#include <initializer_list>

namespace Intel8080 {
    class OutputDevice {
        public:
            OutputDevice(const std::initializer_list<int>& outputPortNumbers);
            virtual ~OutputDevice(){}

            const std::vector<int> outputPortNumbers;

            virtual void writeByte(int portNumber, uint8_t byte) = 0;
    };
}

#endif