
#ifndef LIB1_HPP
#define LIB1_HPP

#include <stdio.h>
#include "LibAbstract.hpp"
#include <SDL2/SDL.h>


class Lib1 : public LibAbstract
{
    SDL_Window *window;
    SDL_Renderer* renderer;
    public:
    Lib1();
    ~Lib1();
    virtual int     WindowCreate(int width, int height);
    virtual void    WindowDestroy();
    virtual int     GetEvents();
};

extern "C" LibAbstract *createLib(void);

#endif