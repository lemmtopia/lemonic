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
#define BLACK 0x000000
#define WHITE 0xFFFFFF

// Math stuff
#define PI 3.1415f

typedef struct vec2_t
{
  float x, y;
} vec2_t;

// Main definitions
void init_window(int width, int height, char* title, uint32_t color);
void update_pixels();
int window_should_close();
void quit_window();

// Shapes
void draw_rect(int x, int y, int width, int height, uint32_t color);
void draw_line(int x1, int y1, int x2, int y2, uint32_t color);

void draw_line(int x1, int y1, int x2, int y2, uint32_t color);
#endif
