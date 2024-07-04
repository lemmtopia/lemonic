#include "lemonic.h"

int main(void)
{
    init_window(320, 180, "hello, lemonic!", 3, CORNBLUE);

    while (!window_should_close())
    {
	clear_screen(TOMATO);
	fill_rect(3, 3, 40, 50, WHITE);
	draw_rect(3, 3, 40, 50, BLACK);
	
	update_dt();
	update_pixels();
    }
    
    quit_window();
    
}
