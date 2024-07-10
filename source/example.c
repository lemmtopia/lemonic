#include "lemonic.h"

int main(void)
{
    const int screen_width = 320;
    const int screen_height = 180;
    const int screen_scale = 3;
    
    init_window(screen_width, screen_height, "hello, lemonic!", screen_scale, CORNBLUE);

    // initialize player variables
    int player_x = screen_width / 2;
    int player_y = screen_height / 2;
    int player_radius = 16;

    int player_speed = 2;
    
    while (!window_should_close())
    {
	player_x += player_speed * (is_key_down(K_D) - is_key_down(K_A));
	player_y += player_speed * (is_key_down(K_S) - is_key_down(K_W));
	
	clear_screen(WHITE);

	fill_circle(player_x, player_y, player_radius, TOMATO);
	draw_circle(player_x, player_y, player_radius, BLACK);
	draw_text("lemonic is cool", 15, 0, 0, TOMATO);
	
	update_dt();
	update_pixels();
    }
    
    quit_window();
}
