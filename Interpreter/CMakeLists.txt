cmake_minimum_required(VERSION 3.30)
project(Chip8-Interpreter VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

add_executable(Interpreter
    main.cpp
    Chip8/chip8.cpp
)