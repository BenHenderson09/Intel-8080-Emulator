project(8080_emulator)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Setup header files
set(HEADER_FILES
    config/OpcodeDetails.hpp
    src/ArithmeticAndLogicFlags/ArithmeticAndLogicFlags.hpp
    src/Processor/Processor.hpp
    src/findNumberOfBytesUsedByOpcode/findNumberOfBytesUsedByOpcode.hpp
    src/UnsupportedOpcodeException/UnsupportedOpcodeException.hpp
    src/BinaryArithmetic/BinaryArithmetic.hpp
    src/Registers/Registers.hpp
    src/RegisterPair/RegisterPair.hpp
    src/ProcessorObserver/ProcessorObserver.hpp)

# Setup source files
set(SOURCE_FILES 
    src/8080_emulator.cpp
    src/Processor/Processor.cpp
    src/Processor/Processor.executeOneByteInstruction.cpp
    src/Processor/Processor.executeTwoByteInstruction.cpp
    src/Processor/Processor.executeThreeByteInstruction.cpp
    src/findNumberOfBytesUsedByOpcode/findNumberOfBytesUsedByOpcode.cpp
    src/UnsupportedOpcodeException/UnsupportedOpcodeException.cpp
    src/BinaryArithmetic/BinaryArithmetic.cpp
    src/RegisterPair/RegisterPair.cpp)

# Setup inline files (for template implementations)
set(INLINE_FILES
    src/BinaryArithmetic/BinaryArithmetic.ipp)

# Create executable
add_executable(8080_emulator ${SOURCE_FILES} ${INLINE_FILES} ${HEADER_FILES})

# Setup libraries
include_directories(deps/FileBuffer/include)
find_library(FILE_BUFFER FileBuffer deps/FileBuffer/lib)

include_directories(deps/SDL2/include)
find_library(SDL2 SDL2 deps/SDL2/lib)

set(LIBRARIES ${FILE_BUFFER} ${SDL2})

target_link_libraries(8080_emulator LINK_PUBLIC ${LIBRARIES})