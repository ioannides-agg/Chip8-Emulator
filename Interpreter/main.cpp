#include "include.h"

int main() {
    std::vector<char> buffer;
    std::string path;

    SDL_Log("%s", "hello sdl");

    std::cout << "Select rom: " << "\n";
    std::cin >> path;
    rr::load_rom(path, buffer);

    chip8 interpreter(buffer);
    while(interpreter.getPC() <= buffer.size() + 0x200) {
        uint8_t* instruction = interpreter.fetch();
        interpreter.decode(instruction);
    }

}