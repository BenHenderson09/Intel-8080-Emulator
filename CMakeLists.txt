project(Intel8080)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Setup include directories
set(INCLUDE_DIRS
    config
    src/ArithmeticAndLogicFlags
    src/findNumberOfBytesUsedByOpcode
    src/UnsupportedOpcodeException
    src/BinaryArithmetic
    src/Registers
    src/RegisterPair
    src/ProcessorObserver)

# Setup source files
set(SOURCE_FILES
    src/Processor.cpp
    src/Processor.executeOneByteInstruction.cpp
    src/Processor.executeTwoByteInstruction.cpp
    src/Processor.executeThreeByteInstruction.cpp
    src/findNumberOfBytesUsedByOpcode/findNumberOfBytesUsedByOpcode.cpp
    src/UnsupportedOpcodeException/UnsupportedOpcodeException.cpp
    src/BinaryArithmetic/BinaryArithmetic.cpp
    src/RegisterPair/RegisterPair.cpp)

# Create the shared library
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Add dependencies
find_library(FILE_BUFFER FileBuffer lib)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${FILE_BUFFER})

# Install library .so file
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

# Install library headers from the include dirs
foreach (INCLUDE_DIR ${INCLUDE_DIRS})
    install(DIRECTORY ${INCLUDE_DIR}
            DESTINATION include/${PROJECT_NAME}
            FILES_MATCHING
            PATTERN "*.*pp" # Accept .hpp and .ipp
    )
endforeach()

install(FILES src/Processor.hpp DESTINATION include/${PROJECT_NAME})