#ifndef CHIP8_H
#define CHIP8_H

#include <iostream>
#include <array>
#include <vector>
#include <cassert>
#include <iomanip>

class chip8_display {
    public:
    
    void flip(int i, int j) {
        display[i][j] != display[i][j];
    }

    void clear() {
        for (size_t i = 0; i < 64; i++)
        {
            /* code */
        }
        
    }

    private:
    std::array< std::array<bool, 64> , 32> display;
};

class chip8_memory {
    public:

    void write(uint16_t address, uint8_t value) {
        memory[address] = value;
    }

    uint8_t read(uint16_t address) {
        return memory[address];
    }

    uint8_t operator[](uint16_t i) const { return memory[i]; }
    uint8_t& operator[](uint16_t i) { return memory[i]; }

    private:
    std::array<uint8_t, 4096> memory;
};

class chip8_stack {
    public:
    void push(uint16_t address) {
        assert((int)SP < 16);
        stack.push_back(address);
        SP++;
    }

    uint16_t pop() {
        assert(!stack.empty());
        auto temp = stack[SP];
        SP--;
        stack.pop_back();
        return temp;
    }

    uint8_t getSP() const {
        return SP;
    }

    private:
    std::vector<uint16_t> stack;
    uint8_t SP;
};

class chip8 {
    public:
    chip8();
    void decode(uint16_t _pc);

    void load(std::vector<char> &buffer);

    uint16_t fetch() {
        uint16_t temp = PC;
        PC++;
        return temp;
    }

    void point(uint16_t address) {
        PC = address;
    }

    private:
    chip8_memory memory;
    std::array<uint8_t, 16> V;
    uint16_t I;
    chip8_stack stack;
    chip8_display display;

    protected:
    uint16_t PC = 0x200;

    static constexpr std::array<uint8_t, 80> font = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
};

#endif