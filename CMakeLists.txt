cmake_minimum_required(VERSION 3.30)
project(Chip8-Emulator VERSION 1.0.0)

add_executable(Chip8-Dissasembler
    Disassembler/Chip8_Disassembler.cpp
)

add_executable(Chip8-Interpreter
    Interpreter/main.cpp
    Interpreter/Chip8/chip8.cpp
)