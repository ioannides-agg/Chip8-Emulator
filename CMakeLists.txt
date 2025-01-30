cmake_minimum_required(VERSION 3.30)
project(Chip8-Emulator VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(Vendored)
add_subdirectory(Interpreter)
add_subdirectory(Disassembler)