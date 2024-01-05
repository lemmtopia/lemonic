#include "lemonic.h"

int main(void)
{ 
    init_window(320, 180, "basic window", 3, CORNBLUE);

    rect_t rect = {40, 80, 80, 60};
    rect_t plr = {160, 90, 32, 32};

    sprite_t spr = load_ppm("face.ppm");
    while (!window_should_close())
    {
        uint32_t color = BLACK;
        uint32_t color2 = WHITE;
        if (rect_vs_rect(plr, rect))
        {
            color = GREEN;
            color2 = TOMATO;
        }

        update_dt();

        clear_screen(CORNBLUE);
        fill_rect(-20, 20, 80, 80, WHITE);
        draw_rect(rect.x, rect.y, rect.width, rect.height, color);
        draw_line(20, 69, 20, 140, TOMATO);
        draw_line(42, 69, 50, 140, TOMATO);
        draw_line(20, 50, 30, 120, TOMATO);
        draw_line(20, 20, 130, 30, TOMATO);
        draw_line(20, 20, 130, 20, TOMATO);
        draw_pixel(3, 3, YELLOW);

        draw_circle(130, 60, 24, YELLOW);
        fill_circle(10, 80, 18, YELLOW);
        fill_circle(110, 90, 6, TOMATO);

        draw_sprite(spr, (int)plr.x, (int)plr.y);
        draw_rect(plr.x, plr.y, plr.width, plr.height, color2);

        int dx = is_key_down(K_D) - is_key_down(K_A);
        int dy = is_key_down(K_S) - is_key_down(K_W);

        plr.x += dx;
        plr.y += dy;

        update_pixels();
    } 

    quit_window();
    return 0;
}
