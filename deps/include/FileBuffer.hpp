#ifndef FILE_BUFFER_HPP
#define FILE_BUFFER_HPP

#include <string>
#include <cstdint>

class FileBuffer {
    public:        
        FileBuffer(const char* fileLocation);
        FileBuffer(const std::string& fileLocation);
        ~FileBuffer();

        uint8_t operator[](long byteIndex) const;

        long getFileSizeInBytes() const;
        void copyBufferContentsToAnotherBuffer(uint8_t*& otherBuffer, long sizeOfOtherBuffer) const;

    private:
        uint8_t* heapBasedBuffer;
        long fileSizeInBytes;

        void writeFileContentsToBuffer(const std::string& fileLocation);
};

#endif