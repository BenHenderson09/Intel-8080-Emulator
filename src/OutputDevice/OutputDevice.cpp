#include <initializer_list>
#include <cstdint>
#include "../Device/Device.hpp"
#include "OutputDevice.hpp"

namespace Intel8080 {
    OutputDevice::OutputDevice(const std::initializer_list<uint8_t>& outputPortNumbers)
        : outputPortNumbers{outputPortNumbers}{}
}