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
                    std::cout << "-";
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
            uint8_t reg = (code0 & 0x0f); //pad the first byte.
            std::cout << "ADD " << "V" << (int)reg << ",#$" << std::setfill('0') << std::setw(2) << code1;
        }
        break;

        case 0x8:
        {
            uint8_t x = (code0 & 0x0f);
            uint8_t y = (code1 >> 4);
            uint8_t last_n = (code1 & 0x0f) >> 4;;
            //TODO: IMPLEMENT 8xyn
            switch (last_n)
            {
            case 0x0: std::cout << "LD " << "V" << (int)x << ",V" << (int)y; break;
            case 0x1: std::cout << "OR " << "V" << (int)x << ",V" << (int)y; break;
            case 0x2: std::cout << "AND " << "V" << (int)x << ",V" << (int)y; break;
            case 0x3: std::cout << "XOR " << "V" << (int)x << ",V" << (int)y; break;
            case 0x4: std::cout << "ADD " << "V" << (int)x << ",V" << (int)y; break;
            case 0x5: std::cout << "SUB " << "V" << (int)x << ",V" << (int)y; break;
            case 0x6: std::cout << "SHR " << "V" << (int)x << "{,V" << (int)y << "}"; break;
            case 0x7: std::cout << "SUBN " << "V" << (int)x << ",V" << (int)y; break;
            case 0xe: std::cout << "SHL " << "V" << (int)x << "{,V" << (int)y << "}"; break;
            
            default:
                break;
            }
        }
        break;

        case 0x9:
        {
            uint8_t reg1 = (code0 & 0x0f); //pad the first byte.
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
        {
            uint8_t x = (code0 & 0x0f);
            uint8_t y = (code1 >> 4);
            uint8_t last_n = (code1 & 0x0f) >> 4;
            std::cout << "DRW " << "V" << (int)x << ",V" << (int)y << "," << (int)last_n;
        }
        break;

        case 0xe:
        {
            uint8_t x = (code0 & 0x0f);
            switch(code1){
                case 0x9E: std::cout << "SKP " << "V" << (int)x;
                case 0xA1: std::cout << "SKNP " << "V" << (int)x;
            }
        }
        break;

        case 0xf:
        {
            uint8_t x = (code0 & 0x0f);
            switch(code1){
                case 0x07: std::cout << "LD " << "V" << std::hex << (int)x << ",DT"; break;
                case 0x0A: std::cout << "LD " << "V" << std::hex << (int)x << ",K"; break;
                case 0x15: std::cout << "LD " << "DT" << ",V" << (int)x; break;
                case 0x18: std::cout << "LD " << "ST" << ",V" << (int)x; break;
                case 0x1E: std::cout << "ADD " << "I" << ",V" << (int)x; break;
                case 0x29: std::cout << "LD " << "F" << ",V" << (int)x; break;
                case 0x33: std::cout << "LD " << "B" << ",V" << (int)x; break;
                case 0x55: std::cout << "LD " << "[I]" << ",V" << (int)x; break;
                case 0x65: std::cout << "LD " << "V" << std::hex << (int)x << ",[I]"; break;
            }
        }
        break;
    }

    
}

int main() { 
    std::ifstream rom;
    rom.open("../roms/ibm.ch8",std::ios::binary);

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