#ifndef RENDERER_H
#define RENDERER_H

#include "SDL3/SDL.h"
#include "settings.h"

class Renderer {
public:
    Renderer(SDL_Window *win, DisplaySettings settings = DisplaySettings{10}) : settings(settings) {
        rend = SDL_CreateRenderer(win, 0);
        if (rend == NULL) {
            SDL_Log("Could not create renderer: %s", SDL_GetError());
            SDL_Quit();
        }

        drawRect.h = drawRect.w = settings.tile_size();
    }

    ~Renderer() {
        SDL_Log("Destroying Renderer!");
        SDL_DestroyRenderer(rend);
    }

    void refresh() {
        SDL_RenderPresent(rend);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE);        // background: black
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend, 255, 255, 255, SDL_ALPHA_OPAQUE);  // pixels: white
    }

    void render(int x, int y) {
        drawRect.x = x * settings.tile_size();
        drawRect.y = y * settings.tile_size();
        SDL_RenderFillRect(rend, &drawRect);
    }

private:
    DisplaySettings settings;
    SDL_Renderer *rend;
    SDL_FRect drawRect;
};

#endif
