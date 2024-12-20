#ifndef CHIP8_H
#define CHIP8_H

class chip8 {
    public:
    chip8();
    void process();

    private:
    chip8_memory memory;
    std::vector<uint8_t> V; //reserve 16 slots
    uint16_t I;
    uint16_t PC;
};

class chip8_memory {
    public:
    chip8_memory() : memory(4096, 0) {};

    void write(std::uint16_t address, std::uint8_t value) {
        memory[address] = value;
    }

    std::uint8_t read(std::uint16_t address) {
        return memory[address];
    }

    private:
    std::vector<uint8_t> memory;
};

#endif