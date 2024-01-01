#include "lemonic.c"
#include "lemonic.h"

int main(void)
{ 
  init_window(640, 480, "basic window", CORNBLUE);

  while (!window_should_close())
  {
    draw_rect(20, 20, 80, 80, WHITE);
    draw_rect(40, 80, 80, 120, BLACK);
    draw_line(20, 20, 50, 80, TOMATO);
    draw_line(20, 10, 80, 180, TOMATO);
    update_pixels();
  } 

  quit_window();
  return 0;
}
