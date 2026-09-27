#ifndef KEYMAP_H
#define KEYMAP_H

#include "SDL3/SDL.h"

//   Keyboard        CHIP-8
//   1 2 3 4         1 2 3 C
//   Q W E R   ->    4 5 6 D
//   A S D F         7 8 9 E
//   Z X C V         A 0 B F
//
// Scancodes are physical key positions, so this works the same on any keyboard layout.
// Returns -1 for keys that aren't part of the keypad.
inline int toChip8Key(SDL_Scancode scancode) {
    switch (scancode) {
        case SDL_SCANCODE_1: return 0x1;
        case SDL_SCANCODE_2: return 0x2;
        case SDL_SCANCODE_3: return 0x3;
        case SDL_SCANCODE_4: return 0xC;

        case SDL_SCANCODE_Q: return 0x4;
        case SDL_SCANCODE_W: return 0x5;
        case SDL_SCANCODE_E: return 0x6;
        case SDL_SCANCODE_R: return 0xD;

        case SDL_SCANCODE_A: return 0x7;
        case SDL_SCANCODE_S: return 0x8;
        case SDL_SCANCODE_D: return 0x9;
        case SDL_SCANCODE_F: return 0xE;

        case SDL_SCANCODE_Z: return 0xA;
        case SDL_SCANCODE_X: return 0x0;
        case SDL_SCANCODE_C: return 0xB;
        case SDL_SCANCODE_V: return 0xF;

        default: return -1;
    }
}

#endif
