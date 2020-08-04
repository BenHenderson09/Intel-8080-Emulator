#include <initializer_list>
#include "OutputDevice.hpp"

namespace Intel8080 {
    OutputDevice::OutputDevice(const std::initializer_list<int>& outputPortNumbers)
        : outputPortNumbers{outputPortNumbers}{}
}