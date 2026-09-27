#ifndef WINDOW_H
#define WINDOW_H

#include "SDL3/SDL.h"
#include "settings.h"

class Window {
public:
    Window(const char *window_name, DisplaySettings settings = DisplaySettings{1}) {
        win = SDL_CreateWindow(window_name, settings.width(), settings.height(), 0);
        if (win == NULL) {
            SDL_Log("Could not create window: %s", SDL_GetError());
            SDL_Quit();
        }
    }

    ~Window() {
        SDL_Log("Destroying Window!");
        SDL_DestroyWindow(win);
    }

    SDL_Window *getWindow() { return win; }

private:
    SDL_Window *win;
};

#endif
