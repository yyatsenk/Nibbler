#ifndef LIB2_HPP
#define LIB2_HPP

#include <stdio.h>
#include "LibAbstract.hpp"
#include <SDL2/SDL.h>

extern "C" void hello(void);

class Lib2 : public LibAbstract
{
    SDL_Window *window;
    SDL_Renderer* renderer;
    public:
    
    Lib2();
    ~Lib2();
    virtual int     WindowCreate(int width, int height);
    virtual void    WindowDestroy();
    virtual int     GetEvents();
};

extern "C" LibAbstract *createLib(void);

#endif