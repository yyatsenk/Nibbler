#include <SDL.h>
#include <stdio.h>
#include "LibAbstract.hpp"
#include "Lib1.hpp"
#include <unistd.h>

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
  /* that occurs.   
                                             */
                                            SDL_Rect texture_rect;
        int i = 10;
        texture_rect.x = 15;  //the x coordinate
        texture_rect.y = 35; // the y coordinate
        texture_rect.w = 100; //the width of the texture
        texture_rect.h = 50; //the height of the texture
    int running = 1;
    int j = 0;
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
            case SDLK_UP:
                    texture_rect.y -=10;
                break;
            case SDLK_DOWN:
                    texture_rect.y +=10;
                break;
            case SDLK_RIGHT:
                    texture_rect.x +=10;
                break;
            case SDLK_LEFT:
                    texture_rect.x -=10;
                break;
            default:
                printf("event.type = %d\n", event.type);
                break;
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,0,255,0,255);
        SDL_RenderFillRect(renderer, &texture_rect);
        SDL_RenderPresent(renderer);
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

         renderer = SDL_CreateRenderer(window, -1, 0);
        
        //GetEvents();
        //do
        //{
            //texture_rect.x++;
            //sleep(1);
            //SDL_RenderClear(renderer);
        
            //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            //SDL_RenderFillRect(renderer, &texture_rect);
            //SDL_RenderPresent(renderer);
        //}while(i--);
    }