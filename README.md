# Intel 8080 Emulator
An emulator for the Intel 8080, which can be used to mimic the behaviour of the original microprocessor.
This allows us to run programs which were written exclusively for the 8080, such as the original
Space Invaders arcade game.

## Program Details
 - Made with C++
 - Built with CMake
 - Installed as a shared library to be used by other projects
 - No thrid party libraries
 
 ## Installation
 Installation is fairly simple, following the standard method of installing a library with CMake. Run as root.
 1. `git clone https://github.com/BenHenderson09/8080-Emulator`
 2. `mkdir -p 8080-Emulator/build && cd 8080-Emulator/build`
 3. `cmake .. && make install`
 
 ## Dependencies
 - `FileBuffer`, a class I made that reads files into a memory buffer. It can be found [here.](https://github.com/BenHenderson09/FileBuffer)