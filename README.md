# CHIP-8 Emulator

A simple CHIP-8 emulator/interpreter written in C++ 17, using the SDL3 library for graphics and input.

## Table of Contents
* [Building](#Building)
* [Running](#Running)
* [References](#References)
* [Screenshots](#Screenshots)

## Building

### Linux/macOS

```
mkdir build
cd build
cmake ..
make
```

## Running

To run a ROM file the following command can be run from within the repository directory:

```./bin/chip8 <Path to ROM> <Display Scale> <CPU Cycle Delay>```

Generally, a display scale of 10 is recommended. The optimal CPU cycle delay may vary across games, so feel free to adjust it to your liking.

ROM files for the CHIP-8 can be found [here](https://github.com/dmatlack/chip8/tree/master/roms).

## References

- [CHIP-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [Building a CHIP-8 Emulator by Austin Morlan](https://austinmorlan.com/posts/chip8_emulator/)

## Screenshots

**Space Invaders [David Winter].ch8**<br>
![Space Invaders [David Winter].ch8](screenshots/2025-12-25-195735_640x320_scrot.png)<br>

**Tetris [Fran Dachille, 1991**<br>
![Tetris [Fran Dachille, 1991].ch8](screenshots/2025-12-26-211504_640x320_scrot.png)<br>
