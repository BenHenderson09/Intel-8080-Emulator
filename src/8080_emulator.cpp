#include <iostream>
#include <exception>
#include <cstdint>
#include <FileBuffer.hpp>
#include "Processor/Processor.hpp"
#include "startEmulation/startEmulation.hpp"

int main(int argc, char** argv){
    try {
        const char* programFileLocation{argv[1]};
        
        FileBuffer program{programFileLocation};
        Processor processor;
        
        startEmulation(processor, program);
    }
    catch (const std::exception& err){
        std::cerr << err.what() << '\n';

        return EXIT_FAILURE;
    }

    return 0;
}