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

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define ABS(x) (((x)>0)?(x):-(x))

#define FONT_WIDTH 5
#define FONT_HEIGHT 7
#define FONT_SIZE (FONT_WIDTH * FONT_HEIGHT)

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

typedef struct rect_t
{
    int x, y, width, height;
} rect_t;

/* main definitions */
void init_window(int width, int height, char* title, int scale, uint32_t color);
void update_dt();
void update_pixels();
int window_should_close();
void quit_window();
void draw_pixel(int x, int y, uint32_t color);
void fill_rect(int x, int y, int width, int height, uint32_t color);
void draw_line(int x1, int y1, int x2, int y2, uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void draw_circle(int x, int y, int r, uint32_t color);
void fill_circle(int x, int y, int r, uint32_t color);
void clear_screen(uint32_t color);
int is_key_down(int key);
sprite_t load_ppm(char* path);
void draw_sprite(sprite_t spr, int x, int y);
int point_vs_rect(vec2_t v, rect_t r);
int rect_vs_rect(rect_t r1, rect_t r2);
int is_letter(char c);
int get_letter_from_char(char c);
void draw_text(const char* text, int length, int x, int y, uint32_t color);

#endif
