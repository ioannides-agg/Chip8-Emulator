#include "include.h"

int main() {
    std::vector<char> buffer;
    std::string path;

    std::cout << "Select rom: " << "\n";
    std::cin >> path;
    rr::load_rom(path, buffer);

    chip8 interpreter;

    uint16_t current_PC = interpreter.fetch();

    while(current_PC <= buffer.size() + 0x200) {
        current_PC = interpreter.fetch();
        //interpreter.decode(current_PC);
    }

}