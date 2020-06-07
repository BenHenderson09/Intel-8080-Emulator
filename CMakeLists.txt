project(8080_emulator)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Setup header files
set(HEADER_FILES 
    config/HardwareSpecifications.hpp
    src/ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp
    src/Processor/Processor.hpp)

# Setup source files
set(SOURCE_FILES 
    src/8080_emulator.cpp
    src/Processor/Processor.cpp)

# Create executable
add_executable(8080_emulator ${SOURCE_FILES} ${HEADER_FILES})