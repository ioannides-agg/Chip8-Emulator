#include "includes.h"

void Dissasembler(std::vector<char> &buffer, int pc) {
    char* code = &buffer[pc];
    int nibble = (int)((unsigned char)code[0] >> 4);

    std::cout << std::hex << pc << " ";
    std::cout << std::setfill('0') << std::setw(2) << (int)(uint8_t)code[0] << " ";
    std::cout << std::setfill('0') << std::setw(2) << (int)(uint8_t)code[1] << " ";
    //std::cout << nibble << " ";
    int code0 = (int)(uint8_t)code[0];
    int code1 = (int)(uint8_t)code[1];

    switch(nibble) {
        case 0x0: 
        {
            switch((int)(uint8_t)code[1]) {
                case 0xE0: //Clear the display.
                    std::cout << "CLS";
                break;

                case 0xEE: //Return from a subroutine.
                    std::cout << "RET";
                break;

                default:
                    std::cout << "UNKNOWN 0";
                break;
            }
            /*uint8_t n = code[0] & 0x0f;
            uint16_t nnn = n << code[1];
            std::cout << "SYS " << "#$" << (int)n << (int)(uint8_t)code[1];*/
        }
        break;
        case 0x1: //Jump to location nnn.
        {
            uint16_t nnn = (code0&0x0f) << 8 | code1;
            std::cout << "JP #$" << nnn;
        }
        break;
        case 0x2:
        {
            uint16_t nnn = (code0&0x0f) << 8 | code1;
            std::cout << "CALL #$" << nnn;
        }
        break;
        case 0x3:
        {
            uint8_t reg = code0 & 0x0f; //pad the first byte.
            std::cout << "SE " << "V" << (int)reg << ",#$" << std::setfill('0') << std::setw(2) << code1;
        }
        break;
        case 0x4:
        {
            uint8_t reg = code0 & 0x0f; //pad the first byte.
            std::cout << "SNE " << "V" << (int)reg << ",#$" << std::setfill('0') << std::setw(2) << code1;
        }
        break;
        case 0x5:
        {
            uint8_t reg1 = code0 & 0x0f; //pad the first byte.
            uint8_t reg2 = code1 >> 4;
            std::cout << "SE " << "V" << (int)reg1 << ",V" << (int)reg2;
        }
        break;

        case 0x6: //6xkk - LD Vx, byte, Set Vx = kk.
        {
            uint8_t reg = code0 & 0x0f; //pad the first byte.
            std::cout << "LD " << "V" << (int)reg << ",#$" << std::setfill('0') << std::setw(2) << code1;
        }
        break;

        case 0x7:
        {
            uint8_t reg = code0 & 0x0f; //pad the first byte.
            std::cout << "ADD " << "V" << (int)reg << ",#$" << std::setfill('0') << std::setw(2) << code1;
        }
        break;

        case 0x8:
            std::cout << "8 not yet implemented";
        break;

        case 0x9:
        {
            uint8_t reg1 = code0 & 0x0f; //pad the first byte.
            uint8_t reg2 = code1 >> 4;
            std::cout << "SNE " << "V" << (int)reg1 << ",V" << (int)reg2;
        }
        break;

        case 0xa: //Annn - LD I, addr, Set I = nnn.
        {
            uint8_t addressI = code[0] & 0x0f;
            std::cout << "LD " << "I,#$" << (int)addressI << code1;
        }
         break;

        case 0xb:
        {
            uint16_t nnn = (code0&0x0f) << 8 | code1;
            std::cout << "JP V0,#$" << nnn;
        }
        break;

        case 0xc:
        {
            uint8_t reg = code0 & 0x0f; //pad the first byte.
            std::cout << "RND " << "V" << (int)reg << ",#$" << std::setfill('0') << std::setw(2) << code1;
        }
        break;

        case 0xd:
            std::cout << "d not yet implemented";
        break;

        case 0xe:
            std::cout << "e not yet implemented";
        break;

        case 0xf:
            std::cout << "f not yet implemented";
        break;
    }

    
}

int main() { 
    std::ifstream rom;
    rom.open("roms/Fishie.ch8",std::ios::binary);

    if (rom.is_open()==false) {
		std::cout << "Cannot open file\n";
        return 1;
	}

	rom.seekg(0, std::ios::end);
    int length = rom.tellg();
    rom.seekg(0, std::ios::beg);

    std::vector<char> buffer(length + 0x200);
    rom.read(&buffer[0 + 0x200], length);

    rom.close();
    
    int pc = 0x200;

    while( pc < (length + 0x200)) {
        Dissasembler(buffer, pc);
        pc += 2;
        std::cout << "\n";
    }

    return 0;
}