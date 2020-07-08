#include "isDeviceAttachedToPort.hpp"

#include <algorithm>

namespace Intel8080 {
    bool isDeviceAttachedToPort(const std::vector<uint8_t>& portNumbers, uint8_t portNumber){
        auto iteratorToPortNumber{
            std::find(
                portNumbers.begin(),
                portNumbers.end(),
                portNumber
            )
        };

        return iteratorToPortNumber != portNumbers.end();
    }
}