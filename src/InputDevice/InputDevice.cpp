#include "InputDevice.hpp"

namespace Intel8080 {
    InputDevice::InputDevice(const std::initializer_list<uint8_t>& portNumbers)
        : Device(portNumbers){}
}