#ifndef CHIP8_H
#define CHIP8_H

#include <array>
#include <vector>
#include <stdexcept>

class chip8_display {
    public:

    bool flip(int x, int y) {
        bool was_on = display[y][x];
        display[y][x] = !display[y][x];
        return was_on;
    }

    void clear() {
        for (auto &row : display) {
            row.fill(false);
        }
    }

    bool get(int x, int y) const { return display[y][x]; }

    private:
    std::array< std::array<bool, 64> , 32> display{};
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
    std::array<uint8_t, 4096> memory{};
};

class chip8_stack {
    public:
    void push(uint16_t address) {
        if (stack.size() >= 16) {
            throw std::runtime_error("Stack overflow: more than 16 nested CALLs");
        }
        stack.push_back(address);
    }

    uint16_t pop() {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow: RET with no matching CALL");
        }
        uint16_t temp = stack.back();
        stack.pop_back();
        return temp;
    }

    private:
    std::vector<uint16_t> stack{};
};

class chip8 {
    public:
    chip8(std::vector<char> &buffer) {
        PC = FONT_START_ADDRESS;
        for (size_t i = 0; i < font.size(); i++)
        {
            memory.write(PC, font[i]);
            PC++;
        }

        load(buffer);
    }

    void load(std::vector<char> &buffer) {
        PC = 0x200;

        for (size_t i = 0; i < buffer.size(); i++)
        {
            memory.write(PC, buffer[i]);
            PC++;
        }

        PC = 0x200;
    }

    void decode(uint16_t opcode) {
        //TODO
    }

    uint16_t fetch() {
        uint16_t opcode = memory[PC] << 8 | memory[PC + 1];
        PC += 2;
        return opcode;
    }

    uint16_t getPC() const {
        return PC;
    }

    const chip8_display &getDisplay() const { return display; }

    private:
    std::array<uint8_t, 16> V{};
    uint16_t I{};
    chip8_memory memory;
    chip8_stack stack;
    chip8_display display;

    protected:
    uint16_t PC = 0x200;

    static constexpr uint16_t FONT_START_ADDRESS = 0x50;

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
