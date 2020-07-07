#ifndef PROCESSOR_OBSERVER_HPP
#define PROCESSOR_OBSERVER_HPP

#include <cstdint>

namespace Intel8080 {
    class ProcessorObserver {
        public:
            virtual ~ProcessorObserver(){}

            virtual void notifyInstructionHasBeenExecuted(uint8_t opcode) = 0;
    };
};

#endif