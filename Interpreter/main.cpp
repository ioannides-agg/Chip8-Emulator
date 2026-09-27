#include <iostream>
#include <vector>
#include "../Libraries/rom_reader.h"
#include "Chip8/Chip8.h"
#include "SDL3/SDL_events.h"
#include "engine/renderer.h"
#include "engine/window.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
      SDL_Log("Could not initialize SDL modules: %s", SDL_GetError());
      SDL_Quit();
      return -1;
    }

    std::vector<char> buffer;
    std::string path;

    std::cout << "Select rom: " << "\n";
    std::cin >> path;
    rr::load_rom(path, buffer);

    chip8 interpreter(buffer);
    while(interpreter.getPC() <= buffer.size() + 0x200) {
        uint16_t opcode = interpreter.fetch();
        interpreter.decode(opcode);
    }

    Window window("Chip-8 Emulator");
    Renderer renderer(window.getWindow());
    bool running = true;

    while(running) {
        { // RENDER LOOP
            renderer.refresh();
        }

        { // EVENT LOOP
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_EVENT_QUIT: running = false; break;

                    case SDL_EVENT_KEY_DOWN:
                        switch (event.key.scancode) {
                            case SDL_SCANCODE_ESCAPE: running = false; break;

                            default: break;
                        }
                    break;
                }
            }
        }
    }

}
