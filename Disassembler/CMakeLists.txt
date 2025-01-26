cmake_minimum_required(VERSION 3.30)
project(Chip8-Disassembler VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

add_executable(Disassembler
    Chip8_Disassembler.cpp
)