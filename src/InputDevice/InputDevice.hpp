#ifndef INPUT_DEVICE_HPP
#define INPUT_DEVICE_HPP

#include <cstdint>
#include <vector>
#include <initializer_list>

namespace Intel8080 {
    class InputDevice {
        public:
            InputDevice(const std::initializer_list<uint8_t>& inputPortNumbers);
            virtual ~InputDevice(){}

            virtual uint8_t readByte(uint8_t portNumber, uint8_t accumulatorState) = 0;

            const std::vector<uint8_t> inputPortNumbers;
    };
}

#endif