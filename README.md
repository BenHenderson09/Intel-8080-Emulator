# Intel 8080 Emulator
An emulator for the Intel 8080, which can be used to mimic the behaviour of the original microprocessor.
This allows us to run programs which were written exclusively for the 8080, such as the original
Space Invaders arcade game.

## Details
- Made with C++
- Built with CMake
- Installed as a shared library to be used by other projects
- Timed to be cycle accurate so programs will run at the same speed as they did on the original 8080.
- No thrid party libraries
- Input and output devices can be emulated via the `InputDevice` and `OutputDevice` classes. They can be "attached"
 to the processor, and the processor will handle reading and writing data via the Strategy pattern.
- Objects can listen for instruction execution. This is done via the `ProcessorObserver` class (Observer pattern).
 
## Installation
Installation is fairly simple, following the usual method of installing a library with CMake. Run as root.
1. `git clone https://github.com/BenHenderson09/Intel-8080-Emulator`
2. `mkdir -p Intel-8080-Emulator/build && cd Intel-8080-Emulator/build`
3. `cmake .. && make install`
 
## Dependencies
- `FileBuffer`, a class I made that reads files into a dynamic memory buffer. It can be found [here.](https://github.com/BenHenderson09/FileBuffer)
## Example
Here's an example of what a program for playing audio may look like.

```C++
#include <Intel8080Emulator/Intel8080.hpp>
#include "SoundCircuitry/SoundCircuitry.hpp"

int main(){
    Intel8080::Processor processor{"path to program file"};
    SoundCircuitry soundCircuitry;
    
    processor.attachOutputDevice(soundCircuitry);
    processor.beginEmulation();
    
    return 0;
}
```
 
## Documentation
Note that all classes are within the `Intel8080` namespace.
 
### Class: `Processor`
```C++
Processor(const std::string& programFilePath);
Processor(const char* programFilePath);
~Processor();

void beginEmulation();
void attachObserver(ProcessorObserver& observer);
void attachInputDevice(InputDevice& device);
void attachOutputDevice(OutputDevice& device);
void interrupt(int interruptHandlerNumber);
bool areInterruptsEnabled() const;
uint8_t readByteFromMemory(uint16_t address) const;
```

- **Constructors**: Simply specify the path of a program file to run.
- `void beginEmulation()`: This will start the fetch-execute cycle from the first memory address.
- `void attachObserver(ProcessorObserver& observer)`: An instance of the `ProcessorObserver`
class is attached to the processor object. The observer will be notified every time the processor
object executes an instruction. Multiple observers can be attached.
- `void attachInputDevice(InputDevice& device)`: An instance of the `InputDevice` class is
attached to the processor object. The processor object will read a byte from the device every time
an `IN` instruction is executed. Multiple devices can be attached.
- `void attachOutputDevice(OutputDevice& device)`: An instance of the `OutputDevice` class is
attached to the processor object. The processor object will write a byte to the device
every time an `OUT` instruction is executed. Multiple devices can be attached.
- `void interrupt(int interruptHandlerNumber)`: This will request the processor object to run
an interrupt handler. There are eight interrupt handlers and each is referenced by a number in
the range 0-7. The handler will only be ran if `bool areInterruptsEnabled() const` returns true.
While the handler is running, `bool areInterruptsEnabled() const` will return false.
- `uint8_t readByteFromMemory(uint16_t address) const`: Returns the byte held at the
specified memory address.

### Class: `ProcessorObserver`
```C++
virtual ~ProcessorObserver(){}

virtual void notifyInstructionHasBeenExecuted() = 0;
```

- `virtual void notifyInstructionHasBeenExecuted() = 0`: The purpose of this pure virtual
function is to allow a `Processor` object to notify any object extending the `ProcessorObserver`
class that an instruction has just finished executing.

### Class: `InputDevice`
```C++
InputDevice(const std::initializer_list<int>& inputPortNumbers);
virtual ~InputDevice(){}

const std::vector<int> inputPortNumbers;

virtual uint8_t readByte(uint8_t portNumber, uint8_t accumulatorState) = 0;
```

- **Constructor**: An `std::initializer_list` of the port numbers which the device is linked
to.

- `const std::vector<int> inputPortNumbers`: The port numbers which the device is linked to
are stored in this vector. This means when a `Processor` object meets an `IN` instruction,
which includes a port number, it can search this vector to find out if the device is linked to
the specified port number or not.

- `virtual uint8_t readByte(uint8_t portNumber, uint8_t accumulatorState) = 0`: A pure virtual
function which allows objects extending the `InputDevice` class
to have data read from them by a `Processor` object when it meets an `IN` instruction.

### Class: `OutputDevice`
```C++
OutputDevice(const std::initializer_list<int>& outputPortNumbers);
virtual ~OutputDevice(){}

const std::vector<int> outputPortNumbers;

virtual void writeByte(uint8_t portNumber, uint8_t byte) = 0;
```

- **Constructor**: An `std::initializer_list` of the port numbers which the device is linked
to.

- `const std::vector<int> outputPortNumbers`: The port numbers which the device is linked to
are stored in this vector. This means when a `Processor` object meets an `OUT` instruction,
which includes a port number, it can search this vector to find out if the device is linked to
the specified port number or not.

- `virtual void writeByte(uint8_t portNumber, uint8_t byte) = 0`: A pure virtual
function which allows objects extending the `OutputDevice` class
to have data written to them by a `Processor` object when it meets an `OUT` instruction.