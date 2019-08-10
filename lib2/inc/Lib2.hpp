#ifndef LIB2_HPP
#define LIB2_HPP

#include <stdio.h>
#include "LibAbstract.hpp"
#include <SDL2/SDL.h>

extern void hello(void);

class Lib2 : public LibAbstract
{
    SDL_Window *window;
    public:
    
    Lib2();
    ~Lib2();
    void Destroy();
};

#endif