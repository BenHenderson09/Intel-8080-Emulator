project(8080_emulator)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Setup header files
set(HEADER_FILES 
    config/HardwareSpecifications.hpp
    config/OpcodeDetails.hpp
    src/ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp
    src/Processor/Processor.hpp
    src/startEmulation/startEmulation.hpp
    src/findNumberOfBytesUsedByOpcode/findNumberOfBytesUsedByOpcode.hpp
    src/UnsupportedOpcodeException/UnsupportedOpcodeException.hpp)

# Setup source files
set(SOURCE_FILES 
    src/8080_emulator.cpp
    src/Processor/Processor.cpp
    src/Processor/Processor.executeOneByteInstruction.cpp
    src/Processor/Processor.executeTwoByteInstruction.cpp
    src/Processor/Processor.executeThreeByteInstruction.cpp
    src/startEmulation/startEmulation.cpp
    src/findNumberOfBytesUsedByOpcode/findNumberOfBytesUsedByOpcode.cpp
    src/UnsupportedOpcodeException/UnsupportedOpcodeException.cpp)

# Create executable
add_executable(8080_emulator ${SOURCE_FILES} ${HEADER_FILES})

# Setup libraries
include_directories(deps/FileBuffer/include)
find_library(FILE_BUFFER FileBuffer deps/FileBuffer/lib)

target_link_libraries(8080_emulator LINK_PUBLIC ${FILE_BUFFER})