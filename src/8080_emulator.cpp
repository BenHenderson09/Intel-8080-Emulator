#include <iostream>
#include <exception>
#include <cstdint>
#include "Processor/Processor.hpp"

int main(int argc, char** argv){
    try {
        Processor processor;
    }
    catch (const std::exception& err){
        std::cerr << err.what() << '\n';
        
        return EXIT_FAILURE;
    }

    return 0;
}