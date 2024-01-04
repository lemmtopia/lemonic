#ifndef LEMONIC_H
#define LEMONIC_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

/* basic defines */
#define LEMONIC_VERSION "0.69"

#define TRUE  1
#define FALSE 0

#define FPS 60
#define TARGET_FRAME_TIME (1000 / FPS)

typedef struct screen_t
{
    int width, height;
    uint32_t* pixels;
} screen_t;

typedef screen_t sprite_t;

#define CORNBLUE 0x7288E5
#define TOMATO 0xD7402B
#define YELLOW 0xFFFF00
#define GREEN 0x00FF00
#define BLACK 0x000000
#define WHITE 0xFFFFFF

enum KEYS
{
    K_A,   
    K_B,   
    K_C,   
    K_D,
    K_E,
    K_F,
    K_G,
    K_H,
    K_I,
    K_J,
    K_K,
    K_L,
    K_M,
    K_N,
    K_O,
    K_P,
    K_Q,
    K_R,
    K_S,
    K_T,
    K_U,
    K_V,
    K_W,
    K_X,
    K_Y,
    K_Z,
};

/* math stuff */
#define PI 3.1415f

typedef struct vec2_t
{
    float x, y;
} vec2_t;

/* data */
static screen_t screen;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;

static float delta_time;
static float last_frame_time;

/* main definitions */
static void init_window(int width, int height, char* title, int scale, uint32_t color)
{ 
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * scale, height * scale, 0);  
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);

    screen.width = width;
    screen.height = height;
    screen.pixels = (uint32_t*)malloc(screen.width * screen.height * sizeof(uint32_t));

    for (int i = 0; i < screen.width * screen.height; i++)
    {
        screen.pixels[i] = color;
    }
}

static void update_dt()
{
    /* get the delta time */
    delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    int delay = TARGET_FRAME_TIME - (SDL_GetTicks() - last_frame_time); 

    if (delay > 0 && delay <= TARGET_FRAME_TIME)
    {
        SDL_Delay(delay);
    }

    /* update the last frame time to calculate stuff again */
    last_frame_time = SDL_GetTicks();
}

static void update_pixels()
{
    SDL_UpdateTexture(texture, NULL, screen.pixels, screen.width * 4);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

static int window_should_close()
{
    SDL_Event ev;
    if (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_QUIT)
        {
            return TRUE;
        }
    }

    return FALSE;
}

static void quit_window()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static void draw_pixel(int x, int y, uint32_t color)
{
    if (x >= 0 && x < screen.width &&
        y >= 0 && y < screen.height)
    {
        screen.pixels[y * screen.width + x] = color;
    }
}

static void fill_rect(int x, int y, int width, int height, uint32_t color)
{
    for (int i = x; i < x + width; i++)
    {
        for (int j = y; j < y + height; j++)
        {
            draw_pixel(i, j, color);
        }
    }
}

static void draw_line(int x1, int y1, int x2, int y2, uint32_t color)
{
    /* get mins and maxs */
    int minx = (int)fmin((double)x1, (double)x2);    
    int maxx = (int)fmax((double)x1, (double)x2);    
    int miny = (int)fmin((double)y1, (double)y2);    
    int maxy = (int)fmax((double)y1, (double)y2);    

    float last_j = 0;
   
    /* check if the difference != 0 */
    if (maxx - minx != 0)
    {
        for (int i = miny; i < maxy; i++)
        {
            int j = 0;
            /* check if the difference != 0 */
            if (maxy - miny != 0)
            {
                j = minx + (maxx - minx) * (i - miny) / (maxy - miny);
            }
            else 
            {
                j = minx + (maxx - minx) * (i - miny);
            }

            /* fill the big gaps */
            if (last_j != 0 && j - last_j > 1)
            {
                for (int k = last_j + 1; k < j; k++)
                {
                    draw_pixel(k, i, color);
                }
            }

            draw_pixel(j, i, color);
            last_j = j;
        }

        if (maxy - miny == 0)
        {
            for (int i = minx; i < maxx; i++)
            {
                draw_pixel(i, maxy, color);
            }
        }
    }
    else 
    {
        for (int i = miny; i < maxy; i++)
        {
            draw_pixel(maxx, i, color);
        }
    }
}

static void draw_rect(int x, int y, int width, int height, uint32_t color)
{
    draw_line(x, y, x + width, y, color);
    draw_line(x, y, x, y + height, color);
    draw_line(x + width, y, x + width, y + height, color);
    draw_line(x, y + height, x + width, y + height, color);
}

static void draw_circle(int x, int y, int r, uint32_t color)
{
    float ang = 0;
    
    for (int i = 0; i < 2 * PI * r; i++)
    {
        ang += PI / (PI * r);
        float xx = cos(ang) * r;
        float yy = sin(ang) * r;
        
        draw_pixel(x + (int)xx, y + (int)yy, color);
    }
}

static void fill_circle(int x, int y, int r, uint32_t color)
{
    float ang = 0;

    for (int i = 0; i < 2 * PI * r; i++)
    {
        ang += PI / (PI * r);
        float xx = cos(ang) * r;
        float yy = sin(ang) * r;

        for (int j = y - yy + 1; j < y + yy - 1; j++)
        {
            draw_line(x + (int)xx, j, x - (int)xx, j, color);
        }
    }   
}

static void clear_screen(uint32_t color)
{
    for (int i = 0; i < screen.width * screen.height; i++)
    {
        screen.pixels[i] = color;
    }
}

static int is_key_down(int key)
{
    const uint8_t* state = SDL_GetKeyboardState(NULL);  

    if (state[key + 4]) 
    {
        return TRUE;
    }

    return FALSE;
}

static sprite_t load_ppm(char* path)
{
    sprite_t spr;

    FILE* file = fopen(path, "r");

    char format[2];
    fscanf(file, "%s\n", format);
    if (strcmp(format, "P6") == 0)
    {
        fscanf(file, "%d %d\n", &spr.width, &spr.height);

        int blah;
        fscanf(file, "%d\n", &blah);

        spr.pixels = (uint32_t*)malloc(spr.width * spr.height * sizeof(uint32_t));

        for (int i = 0; i < spr.width * spr.height; i++)
        {
            uint8_t r, g, b;
            fread(&r, 1, 1, file);
            fread(&g, 1, 1, file);
            fread(&b, 1, 1, file);

            spr.pixels[i] = (r << 16) | (g << 8) | b;
        }
    }

    fclose(file);
    return spr;
}

static void draw_sprite(sprite_t spr, int x, int y)
{
    for (int i = 0; i < spr.width; i++)
    {
        for (int j = 0; j < spr.height; j++)
        {
            draw_pixel(x + i, y + j, spr.pixels[j * spr.width + i]);
        }
    }
}

#endif
