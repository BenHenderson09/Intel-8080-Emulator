#ifndef PROCESSOR_OBSERVER
#define PROCESSOR_OBSERVER

class ProcessorObserver {
    public:
        virtual ~ProcessorObserver(){}

        virtual void notifyInstructionHasBeenExecuted(uint8_t opcode) = 0;
};

#endif