#include <stdio.h>
#include <stdlib.h>
#include "LibAbstract.hpp"
#include "Lib1.hpp"
#include "Lib2.hpp"
#include <unistd.h>
#include <dlfcn.h>
#include <SDL2/SDL.h>

int lib_num = 0;

static char *libs[2] = {
    "/home/yyatsenko/unit/Nibbler/build/lib1/libfirst.so",
    "/home/yyatsenko/unit/Nibbler/build/lib2/libsecond.so"
};

LibAbstract *changeLibrary(void *handle, LibAbstract *(*createLIB)(void))
{
    dlclose(handle);
    if (lib_num == 2)
        lib_num = 0;
    handle = dlopen(libs[lib_num], RTLD_LAZY);
    lib_num++;
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    *(void **) (&createLIB) = dlsym(handle, "createLib");
    return (*createLIB)();
}

void gameLoop(LibAbstract *test, void *handle, LibAbstract *(*createLIB)(void))
{
    test->WindowCreate();
    while (1)
    {
        int code = test->GetEvents();
        printf("%d\n", code);
        if (code == 1)
        {
            test->WindowDestroy();
            test = changeLibrary(handle, createLIB);
            test->WindowCreate();
        }
        if (code == 0)
            break;
    }
    //sleep(5);
    test->WindowDestroy();
}

int main(int argc, char* argv[])
{
/*
    SDL_Window *o;
    SDL_Renderer *r;
    SDL_Event e;
    SDL_Rect q;
    int i =1;
    q.x = 15;  //the x coordinate
        q.y = 35; // the y coordinate
        q.w = 100; //the width of the texture
        q.h = 50; //the height of the texture
    SDL_Init(SDL_INIT_VIDEO);

    o = SDL_CreateWindow("Game test",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            1024,
                            800,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    r = SDL_CreateRenderer(o, -1,SDL_RENDERER_ACCELERATED);

    while(i)
    {
        while(SDL_PollEvent(&e) !=0)
        {
            if(e.type == SDL_QUIT)
                i=0;
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    i=0;
                break;
                case SDLK_UP:
                    q.y -=10;
                break;
                case SDLK_DOWN:
                    q.y +=10;
                break;
                case SDLK_RIGHT:
                    q.x +=10;
                break;
                case SDLK_LEFT:
                    q.x -=10;
                break;
                }
            }
        }
        SDL_SetRenderDrawColor(r,0,0,255,255);
        SDL_RenderClear(r);
        // Creating the rectangle
        //q.x=175;
        //q.y=100;
        //q.h=50;
        //q.w=50;

        SDL_SetRenderDrawColor(r,0,0,0,255);

        SDL_RenderFillRect(r,&q);

        SDL_RenderPresent(r);
    }

    SDL_DestroyWindow(o);
    SDL_DestroyRenderer(r);
    SDL_Quit();

    return 0;
*/
    void *handle;
    void (*hello_world)(void);
    char *error;
    LibAbstract *(*createLIB)(void);

   handle = dlopen("/home/yyatsenko/unit/Nibbler/build/lib2/libsecond.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    *(void **) (&createLIB) = dlsym(handle, "createLib");

   if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    LibAbstract *test = (*createLIB)();
    gameLoop(test, handle, createLIB);
    dlclose(handle);
    return 0;
}
