cmake_minimum_required(VERSION 3.23)

project(CHIP-8-Emulator)

find_package(SDL3 REQUIRED)

add_executable(chip8)
target_sources(chip8
  PRIVATE
    src/main.cpp
    src/chip8.cpp
    src/opcodes.cpp
    src/display.cpp
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      include
    FILES
      include/chip8.h
      include/display.h
)

target_link_libraries(chip8 PRIVATE SDL3::SDL3)

set_target_properties(chip8 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
