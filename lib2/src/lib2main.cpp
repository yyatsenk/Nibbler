#include <SDL.h>
#include <stdio.h>
#include "LibAbstract.hpp"
#include "Lib2.hpp"

void hello(void)
{
    printf("Hello world\n");
}

Lib2::Lib2()
    {
        SDL_Renderer* renderer;

        // Initialize SDL.
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
                return;

        // Create the window where we will draw.
        window = SDL_CreateWindow("SDL_RenderClear",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        512, 512,
                        0);

        // We must call SDL_CreateRenderer in order for draw calls to affect this window.
        renderer = SDL_CreateRenderer(window, -1, 0);

        // Select the color for drawing. It is set to red here.
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);

        // Up until now everything was drawn behind the scenes.
        // This will show the new, red contents of the window.
        SDL_RenderPresent(renderer);
    }
    void Lib2::Destroy()
    {
        SDL_DestroyWindow(window);

        // Clean up
        SDL_Quit();
    }
    Lib2::~Lib2(){}