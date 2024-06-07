#ifndef L_DISPLAY_H
#define L_DISPLAY_H

#include "l_types.h"

// get the window width and height from l_display.c
extern i32 window_width;
extern i32 window_height;

// get the pixels from l_display.c
extern u32* pixels;

// functions
void lemonic_open_window(const char* title, i32 width, i32 height, i32 window_scale);
b8 lemonic_is_running();
void lemonic_update();
void lemonic_close_window();

#endif
