#ifndef OUTPUT_DEVICE_HPP
#define OUTPUT_DEVICE_HPP

#include <cstdint>
#include <vector>
#include <initializer_list>
#include "../Device/Device.hpp"

namespace Intel8080 {
    class OutputDevice : public Device {
        public:
            OutputDevice(const std::initializer_list<uint8_t>& outputPortNumbers);
            virtual ~OutputDevice(){}

            virtual void writeByte(uint8_t portNumber, uint8_t byte) = 0;

            const std::vector<uint8_t> outputPortNumbers;
    };
};

#endif