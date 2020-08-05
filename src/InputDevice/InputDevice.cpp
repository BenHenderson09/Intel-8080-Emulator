#include <cstdint>
#include <initializer_list>
#include "InputDevice.hpp"

namespace Intel8080 {
    InputDevice::InputDevice(const std::initializer_list<uint8_t>& inputPortNumbers)
        : inputPortNumbers{inputPortNumbers}{}
}