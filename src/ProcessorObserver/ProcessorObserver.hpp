#ifndef PROCESSOR_OBSERVER_HPP
#define PROCESSOR_OBSERVER_HPP

namespace Intel8080 {
    class ProcessorObserver {
        public:
            virtual ~ProcessorObserver(){}

            virtual void notifyInstructionHasBeenExecuted() = 0;
    };
}

#endif