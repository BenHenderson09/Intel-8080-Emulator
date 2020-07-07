#include <cstdint>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "findDeviceByPortNumber.hpp"
#include "../Device/Device.hpp"

namespace Intel8080 {
    namespace {
        // Functor to act as a predicate for finding devices
        class isDeviceAttachedToPort {
            public:
                isDeviceAttachedToPort(uint8_t portNumber) : portNumber{portNumber}{}

                bool operator()(Device* device){
                    auto iteratorToSpecifiedPortNumber {
                        std::find (
                            device->portNumbers.begin(),
                            device->portNumbers.end(),
                            portNumber
                        )
                    };

                    return iteratorToSpecifiedPortNumber != device->portNumbers.end();
                }

            private:
                uint8_t portNumber;
        };
    }


    Device* findDeviceByPortNumber(const std::vector<Device*>& devices, uint8_t portNumber){
        auto iteratorToSpecifiedDevice {
            std::find_if(
                devices.begin(),
                devices.end(),
                isDeviceAttachedToPort(portNumber)
            )
        };

        if (iteratorToSpecifiedDevice != devices.end()){
            return *iteratorToSpecifiedDevice;
        }
        else {
            throw std::runtime_error("None of the given devices are attached to the port.");
        }
    }
}