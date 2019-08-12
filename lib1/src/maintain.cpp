#include <SDL.h>
#include <stdio.h>
#include "LibAbstract.hpp"
#include "Lib1.hpp"

LibAbstract *createLib(void)
{
    return new Lib1();
}
Lib1::Lib1()
    {
    }
    void Lib1::WindowDestroy()
    {
        printf("Inside Destroy\n");
        SDL_DestroyWindow(window);

        // Clean up
        SDL_Quit();
    }
    int Lib1::GetEvents()
    {
        printf("Inside Events\n");
        SDL_Event event;
  /* Poll for events. SDL_PollEvent() returns 0 when there are no  */
  /* more events on the event queue, our while loop will exit when */
  /* that occurs.                                              */
    int running = 1;
    while(running)
{
    while(SDL_PollEvent(&event)) // check to see if an event has happened
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_q:
                running = false;
                break;
            case SDLK_m: // if the event is mouse click
                printf("m pressed\n");
                return 1;
                break;
            case SDLK_p:
                printf("p pressed\n");
                return 2;
                break;
            case SDLK_z:
                printf("z pressed\n");
                return 3;
                break;
            default:
                printf("event.type = %d\n", event.type);
                break;
        }
    }
}
    }
    Lib1::~Lib1(){}

    int Lib1::WindowCreate(int width, int height)
    {
        // Initialize SDL.
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
                return -1;

        // Create the window where we will draw.
        window = SDL_CreateWindow("SDL_RenderClear",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        width, height,
                        0);

        SDL_Surface *screen = SDL_GetWindowSurface(window);

    // let's just show some classic code for reference
 /*  SDL_Surface *image = SDL_LoadBMP("/home/yyatsenko/unit/Nibbler/textures/LGHammerTone2.bmp"); // loads image
    printf("%p\n", image);
    SDL_BlitSurface(image, NULL, screen, NULL); // blit it to the screen
    SDL_FreeSurface(image);

    // this works just like SDL_Flip() in SDL 1.2
    SDL_UpdateWindowSurface(window);

    // show image for 2 seconds
    SDL_Delay(2000);*/
        // We must call SDL_CreateRenderer in order for draw calls to affect this window.
         renderer = SDL_CreateRenderer(window, -1, 0);
         //SDL_Texture* texture = IMG_LoadTexture(renderer, "home/yyatsenko/unit/Nibbler/textures/LGHammerTone2.bmp");
        SDL_Rect texture_rect;
        texture_rect.x = 0;  //the x coordinate
        texture_rect.y = 0; // the y coordinate
        texture_rect.w = 50; //the width of the texture
        texture_rect.h = 50; //the height of the texture
        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);
        //SDL_Surface *image = SDL_LoadBMP("/home/yyatsenko/unit/Nibbler/textures/LGHammerTone2.bmp"); // loads image
        //SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, image);
        //SDL_RenderCopy(renderer, newTexture, NULL, NULL); 
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &texture_rect);


        SDL_RenderPresent(renderer);
    }