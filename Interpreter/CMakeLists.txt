add_executable(Interpreter)

target_sources(Interpreter PRIVATE
    main.cpp
    Chip8/chip8.cpp
)

target_include_directories(Interpreter PRIVATE)

target_link_libraries(Interpreter PRIVATE Vendored)