#ifndef INPUT_DEVICE_HPP
#define INPUT_DEVICE_HPP

#include <cstdint>
#include <vector>
#include <initializer_list>

namespace Intel8080 {
    class InputDevice {
        public:
            InputDevice(const std::initializer_list<int>& inputPortNumbers);
            virtual ~InputDevice(){}

            const std::vector<int> inputPortNumbers;

            virtual uint8_t readByte(int portNumber, uint8_t accumulatorState) = 0;
    };
}

#endif