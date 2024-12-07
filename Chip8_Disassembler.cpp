#include "includes.h"

void Dissasembler() {
    

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
        auto code = &buffer[pc];
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)(unsigned char)code[0] << " ";
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)(unsigned char)code[1] << "\n";
        pc += 2;
    }

    return 0;
}