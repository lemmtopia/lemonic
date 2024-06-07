#ifndef L_DRAW_H
#define L_DRAW_H

#include "l_types.h"
#include "l_display.h"

// basic drawing functions
void draw_pixel(i32 x, i32 y, u32 color);
void draw_line(i32 x0, i32 y0, i32 x1, i32 y1, u32 color);
void draw_rect(i32 x, i32 y, i32 width, i32 height, u32 color);
void fill_rect(i32 x, i32 y, i32 width, i32 height, u32 color);

#endif
