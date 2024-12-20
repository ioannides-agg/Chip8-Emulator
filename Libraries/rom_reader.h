#ifndef ROM_READER_H
#define ROM_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cassert>

void load_rom(std::string filepath, std::vector<char> &buffer) {
    std::ifstream rom;
    rom.open(filepath, std::ios::binary);

    auto open = rom.is_open();
    assert(open == true);

	rom.seekg(0, std::ios::end);
    int length = rom.tellg();
    rom.seekg(0, std::ios::beg);

    buffer.resize(length);
    rom.read(&buffer[0 + 0x200], length);

    rom.close();
}

void load_rom(std::string filepath, std::vector<char> &buffer, int surplus) {
    std::ifstream rom;
    rom.open(filepath, std::ios::binary);

    auto open = rom.is_open();
    assert(open == true);

	rom.seekg(0, std::ios::end);
    int length = rom.tellg();
    rom.seekg(0, std::ios::beg);

    buffer.resize(surplus + length);
    rom.read(&buffer[0 + surplus], length);

    rom.close();
}

#endif