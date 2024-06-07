#include "l_draw.h"
#include "l_math.h"

void draw_pixel(i32 x, i32 y, u32 color)
{
    if (x >= 0 && x < window_width && y >= 0 && y < window_height)
    {   
        // only draw inside the screen, duh
        pixels[y * window_width + x] = color;
    }
}

void draw_line(i32 x0, i32 y0, i32 x1, i32 y1, u32 color)
{
    i32 dx = x1 - x0;
    i32 dy = y1 - y0;

    i32 max_delta = int_max(int_abs(dx), int_abs(dy));

    f32 x_inc = (f32)dx / (f32)max_delta;
    f32 y_inc = (f32)dy / (f32)max_delta;

    // go from x0 and y0 to x1 and y1
    f32 cur_x = x0;
    f32 cur_y = y0;

    for (i32 i = 0; i <= max_delta; i++)
    {
        draw_pixel(cur_x, cur_y, color);

        cur_x += x_inc; 
        cur_y += y_inc; 
    }
}

void draw_rect(i32 x, i32 y, i32 width, i32 height, u32 color)
{
    draw_line(x, y, x + width, y, color);
    draw_line(x, y + height, x + width, y + height, color);
    draw_line(x + width, y, x + width, y + height, color);
    draw_line(x, y, x, y + height, color);
}

void fill_rect(i32 x, i32 y, i32 width, i32 height, u32 color)
{
    for (int i = 0; i < height; i++)
    {
        draw_line(x, y + i, x + width, y + i, color);
    }
}
