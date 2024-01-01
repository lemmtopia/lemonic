#include "lemonic.h"

int main(void)
{ 
  init_window(320, 180, "basic window", 3, CORNBLUE);

  while (!window_should_close())
  {
    draw_rect(-20, 20, 80, 80, WHITE);
    draw_rect(40, 80, 80, 180, BLACK);
    draw_line(20, 69, 20, 140, TOMATO);
    draw_line(42, 69, 50, 140, TOMATO);
    draw_line(20, 50, 30, 120, TOMATO);
    draw_line(20, 20, 130, 30, TOMATO);
    draw_line(20, 20, 130, 20, TOMATO);
    draw_pixel(3, 3, YELLOW);

    draw_circle(130, 60, 24, YELLOW);
    fill_circle(130, 60, 18, YELLOW);
    fill_circle(110, 90, 6, TOMATO);
    update_pixels();
  } 

  quit_window();
  return 0;
}
