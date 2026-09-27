#include "Chip8.h"

constexpr uint16_t FONT_START_ADDRESS = 0x50;

chip8::chip8(std::vector<char> &buffer) {
    PC = FONT_START_ADDRESS;
    for (size_t i = 0; i <= font.size(); i++)
    {
        memory.write(PC, font[i]);
        PC++;
    }

    load(buffer);
}

void chip8::load(std::vector<char> &buffer) {
    PC = 0x200;

    for (size_t i = 0; i <= buffer.size(); i++)
    {
        memory.write(PC, buffer[i]);
        PC++;
    }

    PC = 0x200;
}

void chip8::decode(uint8_t* code) {
    int code0 = (int)code[0];
    int code1 = (int)code[1];

    int nibble = (uint8_t)code[0] >> 4;
    //std::cout << code << "\n";

    /*switch (nibble)
    {
        case 0x0:
        {

        }
        break;
    }*/

   PC++;
}
