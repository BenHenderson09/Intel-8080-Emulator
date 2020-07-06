#ifndef INPUT_DEVICE
#define INPUT_DEVICE

#include <cstdint>

namespace Intel8080 {
    class InputDevice {
        public:
            InputDevice(int portNumber);
            virtual ~InputDevice(){}

            virtual uint8_t readByte() const = 0;

            const int portNumber;
    };
};

#endif