#ifndef CHIP8_H
#define CHIP8_H

#include <array>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <random>

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

    //addresses wrap at 4KB (& 0x0fff) so a bad I or PC can never read or write outside the array.
    void write(uint16_t address, uint8_t value) {
        memory[address & 0x0fff] = value;
    }

    uint8_t read(uint16_t address) const {
        return memory[address & 0x0fff];
    }

    uint8_t operator[](uint16_t i) const { return memory[i & 0x0fff]; }
    uint8_t& operator[](uint16_t i) { return memory[i & 0x0fff]; }

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

class chip8_keypad {
    public:
    void set(uint8_t key, bool pressed) {
        keys[key & 0x0F] = pressed;
    }

    bool isPressed(uint8_t key) const {
        return keys[key & 0x0F];
    }

    private:
    std::array<bool, 16> keys{};
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
        int code0 = opcode >> 8;
        int code1 = opcode & 0x00ff;
        int nibble = code0 >> 4;

        switch(nibble) {
            case 0x0:
            {
                switch(code1) {
                    case 0xE0: //Clear the display.
                        display.clear();
                    break;

                    case 0xEE: //Return from a subroutine.
                        PC = stack.pop();
                    break;

                    default: //0nnn - SYS addr, only used by the original hardware, ignored.
                    break;
                }
            }
            break;
            case 0x1: //Jump to location nnn.
            {
                uint16_t nnn = (code0&0x0f) << 8 | code1;
                PC = nnn;
            }
            break;
            case 0x2: //Call subroutine at nnn.
            {
                uint16_t nnn = (code0&0x0f) << 8 | code1;
                stack.push(PC);
                PC = nnn;
            }
            break;
            case 0x3: //3xkk - SE Vx, byte, Skip next instruction if Vx = kk.
            {
                uint8_t reg = code0 & 0x0f;
                if (V[reg] == code1) PC += 2;
            }
            break;
            case 0x4: //4xkk - SNE Vx, byte, Skip next instruction if Vx != kk.
            {
                uint8_t reg = code0 & 0x0f;
                if (V[reg] != code1) PC += 2;
            }
            break;
            case 0x5: //5xy0 - SE Vx, Vy, Skip next instruction if Vx = Vy.
            {
                uint8_t reg1 = code0 & 0x0f;
                uint8_t reg2 = code1 >> 4;
                if (V[reg1] == V[reg2]) PC += 2;
            }
            break;

            case 0x6: //6xkk - LD Vx, byte, Set Vx = kk.
            {
                uint8_t reg = code0 & 0x0f;
                V[reg] = code1;
            }
            break;

            case 0x7: //7xkk - ADD Vx, byte, Set Vx = Vx + kk, no carry flag.
            {
                uint8_t reg = (code0 & 0x0f);
                V[reg] += code1;
            }
            break;

            case 0x8:
            {
                uint8_t x = (code0 & 0x0f);
                uint8_t y = (code1 >> 4);
                uint8_t last_n = (code1 & 0x0f);

                //the flag is always written last, so it wins if x is VF.
                switch (last_n)
                {
                case 0x0: V[x] = V[y]; break;
                case 0x1: V[x] |= V[y]; break;
                case 0x2: V[x] &= V[y]; break;
                case 0x3: V[x] ^= V[y]; break;
                case 0x4: { uint16_t sum = V[x] + V[y]; V[x] = sum & 0xff; V[0xF] = sum > 0xff; } break;
                case 0x5: { bool no_borrow = V[x] >= V[y]; V[x] -= V[y]; V[0xF] = no_borrow; } break;
                case 0x6: { bool bit = V[x] & 0x01; V[x] >>= 1; V[0xF] = bit; } break; //modern behaviour: shifts Vx in place, ignores Vy.
                case 0x7: { bool no_borrow = V[y] >= V[x]; V[x] = V[y] - V[x]; V[0xF] = no_borrow; } break;
                case 0xe: { bool bit = V[x] >> 7; V[x] <<= 1; V[0xF] = bit; } break; //modern behaviour: shifts Vx in place, ignores Vy.

                default: break;
                }
            }
            break;

            case 0x9: //9xy0 - SNE Vx, Vy, Skip next instruction if Vx != Vy.
            {
                uint8_t reg1 = (code0 & 0x0f);
                uint8_t reg2 = code1 >> 4;
                if (V[reg1] != V[reg2]) PC += 2;
            }
            break;

            case 0xa: //Annn - LD I, addr, Set I = nnn.
            {
                uint16_t nnn = (code0&0x0f) << 8 | code1;
                I = nnn;
            }
            break;

            case 0xb: //Bnnn - JP V0, addr, Jump to location nnn + V0.
            {
                uint16_t nnn = (code0&0x0f) << 8 | code1;
                PC = nnn + V[0];
            }
            break;

            case 0xc: //Cxkk - RND Vx, byte, Set Vx = random byte AND kk.
            {
                uint8_t reg = code0 & 0x0f;
                V[reg] = randomByte() & code1;
            }
            break;

            case 0xd: //Dxyn - DRW Vx, Vy, nibble, Draw an n byte sprite from I at (Vx, Vy), VF = collision.
            {
                uint8_t x = (code0 & 0x0f);
                uint8_t y = (code1 >> 4);
                uint8_t last_n = (code1 & 0x0f);

                //the starting position wraps around the screen, the sprite itself gets clipped at the edges.
                int start_x = V[x] % 64;
                int start_y = V[y] % 32;
                V[0xF] = 0;

                for (int row = 0; row < last_n && start_y + row < 32; row++) {
                    uint8_t sprite = memory.read(I + row);

                    for (int col = 0; col < 8 && start_x + col < 64; col++) {
                        if (sprite & (0x80 >> col)) {
                            if (display.flip(start_x + col, start_y + row)) V[0xF] = 1;
                        }
                    }
                }
            }
            break;

            case 0xe:
            {
                uint8_t x = (code0 & 0x0f);
                switch(code1){
                    case 0x9E: if (keypad.isPressed(V[x])) PC += 2; break;
                    case 0xA1: if (!keypad.isPressed(V[x])) PC += 2; break;

                    default: break;
                }
            }
            break;

            case 0xf:
            {
                uint8_t x = (code0 & 0x0f);
                switch(code1){
                    case 0x07: V[x] = delay_timer; break;
                    case 0x0A: //wait for a key press by repeating this instruction until one is down.
                    {
                        bool pressed = false;
                        for (uint8_t key = 0; key < 16; key++) {
                            if (keypad.isPressed(key)) {
                                V[x] = key;
                                pressed = true;
                                break;
                            }
                        }
                        if (!pressed) PC -= 2;
                    }
                    break;
                    case 0x15: delay_timer = V[x]; break;
                    case 0x18: sound_timer = V[x]; break;
                    case 0x1E: I += V[x]; break;
                    case 0x29: I = FONT_START_ADDRESS + (V[x] & 0x0f) * 5; break; //each font character is 5 bytes.
                    case 0x33: //store the hundreds, tens and ones digits of Vx at I, I+1, I+2.
                        memory.write(I, V[x] / 100);
                        memory.write(I + 1, (V[x] / 10) % 10);
                        memory.write(I + 2, V[x] % 10);
                    break;
                    case 0x55: //store V0 to Vx in memory starting at I, modern behaviour: I is left unchanged.
                        for (int i = 0; i <= x; i++) memory.write(I + i, V[i]);
                    break;
                    case 0x65: //read V0 to Vx from memory starting at I, modern behaviour: I is left unchanged.
                        for (int i = 0; i <= x; i++) V[i] = memory.read(I + i);
                    break;

                    default: break;
                }
            }
            break;
        }
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

    void tickTimers() {
        if (delay_timer > 0) delay_timer--;
        if (sound_timer > 0) sound_timer--;
    }

    bool isSoundPlaying() const {
        return sound_timer > 0;
    }

    void setKey(uint8_t key, bool pressed) {
        keypad.set(key, pressed);
    }

    private:
    std::array<uint8_t, 16> V{};
    uint16_t I{};
    uint8_t delay_timer{};
    uint8_t sound_timer{};
    chip8_memory memory;
    chip8_stack stack;
    chip8_display display;
    chip8_keypad keypad;
    std::mt19937 rng{std::random_device{}()};

    uint8_t randomByte() {
        return std::uniform_int_distribution<int>(0, 255)(rng);
    }

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
