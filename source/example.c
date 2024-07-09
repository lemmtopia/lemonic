#include "lemonic.h"

int main(void)
{
    init_window(320, 180, "hello, lemonic!", 3, CORNBLUE);

    while (!window_should_close())
    {
	clear_screen(WHITE);
	fill_rect(3, 39, 40, 50, CORNBLUE);
	draw_rect(3, 39, 40, 50, BLACK);

	draw_line(30, 30, 90, 50, BLACK);
	draw_line(80, 140, 190, 120, BLACK);

	fill_circle(160, 90, 16, BLACK);
	fill_circle(160, 90, 15, TOMATO);
	draw_text("gabriel is cool", 15, 0, 0, TOMATO);
	
	update_dt();
	update_pixels();
    }
    
    quit_window();
    
}
