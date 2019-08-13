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

#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

const SDL_Color BLACK = { .r = 0, .g = 0, .b = 0, .a = 255 };
const SDL_Color WHITE = { .r = 255, .g = 255, .b = 255, .a = 255 };

const SDL_Color RED = { .r = 255, .g = 0, .b = 0, .a = 255 };
const SDL_Color MAROON =  { .r = 128, .g = 0, .b = 0, .a = 255 };

const SDL_Color BLUE = { .r = 0, .g = 0, .b = 255, .a = 255 };
const SDL_Color NAVY = { .r = 0, .g = 0, .b = 128, .a = 255 };

const SDL_Color LIME = { .r = 0, .g = 255, .b = 0, .a = 255 };
const SDL_Color GREEN = { .r = 0, .g = 128, .b = 0, .a = 255 };

// 4:3 aspect ratio is assumed
//
// FIELD_CELL_WIDTH has to divisible by 4, will have to divide SCREEN_WIDTH
#define FIELD_CELL_WIDTH 16
#define CELL_SIZE ((SCREEN_WIDTH) / (FIELD_CELL_WIDTH))
#define FIELD_CELL_HEIGHT ((FIELD_CELL_WIDTH) / 4 * 3)

#define FIELD_START_CELL_X 0
#define FIELD_START_CELL_Y 0

void draw_field(SDL_Renderer *renderer)
{
    SDL_Color prev;
    SDL_GetRenderDrawColor(renderer, &prev.a, &prev.g, &prev.b, &prev.a);

    SDL_SetRenderDrawColor(renderer, NAVY.r, NAVY.g, NAVY.b, NAVY.a);
    SDL_Rect field = {
        FIELD_START_CELL_X * CELL_SIZE,
        FIELD_START_CELL_Y * CELL_SIZE,
        FIELD_CELL_WIDTH * CELL_SIZE,
        FIELD_CELL_HEIGHT * CELL_SIZE
    };

    SDL_RenderFillRect(renderer, &field);
    SDL_SetRenderDrawColor(renderer, BLUE.r, BLUE.g, BLUE.b, BLUE.a);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
    for (int i = 1; i < FIELD_CELL_WIDTH; i++) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0,
                i * CELL_SIZE, FIELD_CELL_HEIGHT * CELL_SIZE);
    }
    for (int i = 1; i < FIELD_CELL_HEIGHT; i++) {
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE,
                FIELD_CELL_WIDTH * CELL_SIZE, i * CELL_SIZE);
    }

    SDL_SetRenderDrawColor(renderer, prev.a, prev.g, prev.b, prev.a);
}

bool is_cell_occupied[FIELD_CELL_HEIGHT][FIELD_CELL_WIDTH];

typedef struct apple {
    int r;
    int c;
} Apple;

Apple apple;

void place_apple()
{
    do {
        apple.r = rand() % FIELD_CELL_HEIGHT;
        apple.c = rand() % FIELD_CELL_WIDTH;
    } while (is_cell_occupied[apple.r][apple.c]);
}

void draw_apple(SDL_Renderer *renderer)
{
    SDL_Color prev;
    SDL_GetRenderDrawColor(renderer, &prev.r, &prev.g, &prev.b, &prev.a);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);

    SDL_Rect apple_cell = {
        .x = apple.c * CELL_SIZE, .y = apple.r * CELL_SIZE,
        .w = CELL_SIZE, .h = CELL_SIZE
    };
    SDL_RenderFillRect(renderer, &apple_cell);
    SDL_SetRenderDrawColor(renderer, MAROON.r, MAROON.g, MAROON.b,
            MAROON.a);
    SDL_RenderDrawRect(renderer, &apple_cell);
    SDL_SetRenderDrawColor(renderer, prev.r, prev.g, prev.b, prev.a);
}

typedef enum dir {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
} Dir;

// change in rows and cols when one moves in that direction by one cell
void get_dr_dc(int *dr, int *dc, Dir dir)
{
    switch (dir) {
    case UP:
        *dr = -1;
        *dc = 0;
        break;
    case DOWN:
        *dr = 1;
        *dc = 0;
        break;
    case RIGHT:
        *dr = 0;
        *dc = 1;
        break;
    case LEFT:
        *dr = 0;
        *dc = -1;
        break;
    default:
        *dr = 0;
        *dc = 0;
        break;
    }
}

typedef struct snake_segment {
    int r;
    int c;
    Dir dir;

    // struct snake_segment *next;
    // struct snake_segment *prev;
} SnakeSegment;

#define SNAKE_MAX_SIZE 10000

typedef struct snake {
    SnakeSegment segments[SNAKE_MAX_SIZE];
    int size;
} Snake;

Snake snake;

Dir snake_get_dir()
{
    if (snake.size == 0) {
        return snake.segments[0].dir;
    }

    return snake.segments[0].dir;
}

void snake_set_dir(Dir dir)
{
    if (snake.size != 0) {
        snake.segments[0].dir = dir;
    }
}

void snake_init_segment(int i)
{
    snake.segments[i] = (SnakeSegment){ 0, 0, RIGHT };
}

void snake_init(int size, int r, int c, Dir dir)
{
    snake.size = size;
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            snake.segments[i].r = r;
            snake.segments[i].c = c;
        } else {
            int dr, dc;
            get_dr_dc(&dr, &dc, snake.segments[i - 1].dir);
            snake.segments[i].r = snake.segments[i - 1].r - dr;
            snake.segments[i].c = snake.segments[i - 1].c - dc;
        }
        snake.segments[i].dir = dir;
        is_cell_occupied[snake.segments[i].r][snake.segments[i].c] = true;
    }
}

void snake_increment_size(const SnakeSegment *new_segment)
{
    snake.segments[snake.size++] = *new_segment;
}

bool is_valid_move(int new_head_r, int new_head_c)
{
    if (new_head_r >= FIELD_CELL_HEIGHT || new_head_r < 0 ||
            new_head_c >=FIELD_CELL_WIDTH || new_head_c < 0 ||
            (is_cell_occupied[new_head_r][new_head_c] &&
             !(new_head_r == snake.segments[snake.size - 1].r &&
                 new_head_c == snake.segments[snake.size - 1].c))) {
        // printf("False move: new_head_r = %d new_head_c = %d\n", new_head_r,
        //      new_head_c);
        return false;
    }

    return true;
}

// will return false on invalid move
bool move_snake(bool *has_eaten_apple)
{
    *has_eaten_apple = false;
    int dr, dc;
    get_dr_dc(&dr, &dc, snake.segments[0].dir);

    if (!is_valid_move(snake.segments[0].r + dr, snake.segments[0].c + dc)) {
        return false;
    }

    for (int i = snake.size - 1; i >= 0; i--) {
        if (i == snake.size - 1) {
            is_cell_occupied[snake.segments[i].r][snake.segments[i].c] = false;

            // get the change in head directions
            get_dr_dc(&dr, &dc, snake.segments[0].dir);
            // if eaten apple, increment the size
            if (snake.segments[0].r + dr == apple.r &&
                    snake.segments[0].c + dc == apple.c) {
                snake_increment_size(&snake.segments[snake.size - 1]);
                is_cell_occupied[snake.segments[i + 1].r][snake.
                    segments[i + 1].c] = true;
                *has_eaten_apple = true;
            }
        }

        get_dr_dc(&dr, &dc, snake.segments[i].dir);
        snake.segments[i].r += dr;
        snake.segments[i].c += dc;

        // for the head
        if (i == 0) {
            is_cell_occupied[snake.segments[i].r][snake.segments[i].c] = true;
        }
    }

    for (int i = snake.size - 1; i >= 1; i--) {
        snake.segments[i].dir = snake.segments[i - 1].dir;
    }

    return true;
}

void draw_snake(SDL_Renderer *renderer)
{
    SDL_Color prev;
    SDL_GetRenderDrawColor(renderer, &prev.a, &prev.g, &prev.b, &prev.a);
    for (int i = 0; i < snake.size; i++) {
        SDL_Rect cell = { snake.segments[i].c * CELL_SIZE,
            snake.segments[i].r * CELL_SIZE,
            CELL_SIZE, CELL_SIZE
        };

        SDL_SetRenderDrawColor(renderer, LIME.r, LIME.g, LIME.b, LIME.a);
        SDL_RenderFillRect(renderer, &cell);

        SDL_SetRenderDrawColor(renderer,GREEN.r,GREEN.g,GREEN.b, 255);
        SDL_RenderDrawRect(renderer, &cell);
    }

    SDL_SetRenderDrawColor(renderer, prev.a, prev.g, prev.b, prev.a);
}

void draw_screen(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_field(renderer);
    draw_apple(renderer);
    draw_snake(renderer);
}

#define FRAME_RATE 60
// snake will move after N_FRAMES_PER_MOVEMENT frames
#define N_FRAMES_PER_MOVEMENT 10

void update_game_state()
{
    bool has_eaten_apple = false;
    if (!move_snake(&has_eaten_apple)) {
        exit(0);
    }

    if (has_eaten_apple) {
        place_apple();
    }
}

int main()
{
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);

    SDL_Window *window =
        SDL_CreateWindow("Snake",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
        );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // make the scaled rendering look smoother.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    int quit = 0;
    snake_init(5, 0, 4, RIGHT);
    place_apple();
    draw_screen(renderer);
    bool last_move_drawn = true;
    int n_frames_mod = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = 1;
                    break;
                case SDLK_UP:
                    if (snake_get_dir() != DOWN && snake_get_dir() != UP &&
                            last_move_drawn) {
                        snake_set_dir(UP);
                        last_move_drawn = false;
                    }
                    break;
                case SDLK_DOWN:
                    if (snake_get_dir() != UP && snake_get_dir() != DOWN &&
                            last_move_drawn) {
                        snake_set_dir(DOWN);
                        last_move_drawn = false;
                    }
                    break;
                case SDLK_LEFT:
                    if (snake_get_dir() != RIGHT && snake_get_dir() != LEFT &&
                            last_move_drawn) {
                        snake_set_dir(LEFT);
                        last_move_drawn = false;
                    }
                    break;
                case SDLK_RIGHT:
                    if (snake_get_dir() != LEFT && snake_get_dir() != RIGHT &&
                            last_move_drawn) {
                        snake_set_dir(RIGHT);
                        last_move_drawn = false;
                    }
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        if (n_frames_mod == 0) {
            update_game_state();
            last_move_drawn = true;
        }

        draw_screen(renderer);
        SDL_RenderPresent(renderer);
        n_frames_mod = (n_frames_mod + 1) % N_FRAMES_PER_MOVEMENT;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}

//int main(int argc, char* argv[])
//{
/*
   

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
    return 0;*/
//}
