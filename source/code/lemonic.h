#ifndef LEMONIC_H
#define LEMONIC_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

// Basic defines
#define LEMONIC_VERSION "0.69"

#define TRUE  1
#define FALSE 0

typedef struct screen_t
{
  int width, height;
  uint32_t* pixels;
} screen_t;

#define CORNBLUE 0x7288E5
#define TOMATO 0xD7402B
#define YELLOW 0xFFFF00
#define BLACK 0x000000
#define WHITE 0xFFFFFF

// Math stuff
#define PI 3.1415f

typedef struct vec2_t
{
  float x, y;
} vec2_t;

// Data
static screen_t screen;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;

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

static void draw_rect(int x, int y, int width, int height, uint32_t color)
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
    int minx = (int)fmin((double)x1, (double)x2);    
    int maxx = (int)fmax((double)x1, (double)x2);    
    int miny = (int)fmin((double)y1, (double)y2);    
    int maxy = (int)fmax((double)y1, (double)y2);    

   
    for (int i = miny; i < miny + maxy; i++)
    {
        int j;
        if (maxy - miny != 0)
        {
            j = minx + (maxx - minx) * (i - miny) / (maxy - miny);
        }
        else 
        {
            j = minx + (maxx - minx) * (i - miny);
        }
        draw_pixel(i, j, color);
    }
}

#endif
