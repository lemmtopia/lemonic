#include "lemonic.c"

int main(void)
{ 
  init_window(640, 480, "basic window", CORNBLUE);

  while (!window_should_close())
  {
    draw_rect(20, 20, 80, 80, WHITE);
    draw_rect(40, 80, 80, 120, BLACK);
    update_pixels();
  } 

  quit_window();
  return 0;
}