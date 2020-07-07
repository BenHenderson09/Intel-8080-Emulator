#ifndef OUTPUT_DEVICE
#define OUTPUT_DEVICE

#include <cstdint>
#include <vector>
#include <initializer_list>
#include "../Device/Device.hpp"

namespace Intel8080 {
    class OutputDevice : public Device {
        public:
            OutputDevice(const std::initializer_list<uint8_t>& portNumbers);
            virtual ~OutputDevice(){}

            virtual uint8_t writeByte(uint8_t portNumber, uint8_t byte) const = 0;
    };
};

#endif