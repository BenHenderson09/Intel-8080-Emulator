#ifndef INPUT_DEVICE_HPP
#define INPUT_DEVICE_HPP

#include <cstdint>
#include <vector>
#include <initializer_list>
#include "../Device/Device.hpp"

namespace Intel8080 {
    class InputDevice : public Device {
        public:
            InputDevice(const std::initializer_list<uint8_t>& portNumbers);
            virtual ~InputDevice(){}

            virtual uint8_t readByte(uint8_t portNumber) const = 0;
    };
};

#endif