#include "lemonic.h"

int main(void)
{ 
    init_window(320, 180, "basic window", 3, CORNBLUE);

    float x = 100;
    float y = 100;

    sprite_t spr = load_ppm("face.ppm");
    while (!window_should_close())
    {
        update_dt();

        clear_screen(CORNBLUE);
        fill_rect(-20, 20, 80, 80, WHITE);
        draw_rect(40, 80, 80, 180, BLACK);
        draw_line(20, 69, 20, 140, TOMATO);
        draw_line(42, 69, 50, 140, TOMATO);
        draw_line(20, 50, 30, 120, TOMATO);
        draw_line(20, 20, 130, 30, TOMATO);
        draw_line(20, 20, 130, 20, TOMATO);
        draw_pixel(3, 3, YELLOW);

        draw_circle(130, 60, 24, YELLOW);
        fill_circle(10, 80, 18, YELLOW);
        fill_circle(110, 90, 6, TOMATO);

        draw_sprite(spr, (int)x, (int)y);
        int dx = is_key_down(K_D) - is_key_down(K_A);
        int dy = is_key_down(K_S) - is_key_down(K_W);

        x += dx;
        y += dy;

        update_pixels();
    } 

    quit_window();
    return 0;
}
