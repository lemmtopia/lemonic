#include "lemonic.h"

int main(void)
{ 
  init_window(320, 180, "basic window", 3, CORNBLUE);

  while (!window_should_close())
  {
    draw_rect(-20, 20, 80, 80, WHITE);
    draw_rect(40, 80, 80, 180, BLACK);
    draw_line(20, 69, 50, 120, TOMATO);
    draw_line(42, 69, 50, 160, TOMATO);
    draw_pixel(3, 3, YELLOW);
    update_pixels();
  } 

  quit_window();
  return 0;
}
