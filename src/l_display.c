#include "l_display.h"

#include <stdlib.h>
#include <SDL2/SDL.h>

static SDL_Window* window;
static SDL_Renderer* renderer;
static b8 is_running;

static SDL_Texture* backbuffer;
u32* pixels;

i32 window_width;
i32 window_height;

void lemonic_open_window(const char* title, i32 width, i32 height, i32 window_scale)
{
    if (window_scale < 1)
    {
        // TODO: logging
        return;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        // TODO: logging
        return;
    }

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, 0);

    if (!window)
    {
        // TODO: logging
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        // TODO: logging
        return;
    }

    backbuffer = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGB888,
            SDL_TEXTUREACCESS_STREAMING,
            width / window_scale, height / window_scale);

    window_width = width / window_scale;
    window_height = height / window_scale;

    // 4 bytes per pixel
    pixels = malloc(window_width * window_height * sizeof(u32));
    memset(pixels, 0, window_width * window_height * sizeof(u32));

    is_running = TRUE;
}

b8 lemonic_is_running()
{
    return is_running;
}

void lemonic_update()
{
    SDL_Event ev;
    SDL_PollEvent(&ev);

    if (ev.type == SDL_QUIT) is_running = FALSE;
    
    SDL_UpdateTexture(backbuffer, 0, pixels, window_width * 4);
    SDL_RenderCopy(renderer, backbuffer, 0, 0);
    SDL_RenderPresent(renderer);
}

void lemonic_close_window()
{
    SDL_DestroyTexture(backbuffer);
    free(pixels);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
