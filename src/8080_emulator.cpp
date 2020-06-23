#include <iostream>
#include <exception>
#include <cstdint>
#include <FileBuffer.hpp>
#include "Processor/Processor.hpp"

int main(int argc, char** argv){
    try {
        Processor processor{argv[1]};

        processor.beginEmulation();
    }
    catch (const std::exception& err){
        std::cerr << err.what() << '\n';

        return 1;
    }

    return 0;
}