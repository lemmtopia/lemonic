#include "lemonic.h"

void init_window(int width, int height, char* title, uint32_t color)
{ 
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);  
  renderer = SDL_CreateRenderer(window, -1, 0);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);

  screen.width = width;
  screen.height = height;
  screen.pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));

  for (int i = 0; i < width * height; i++)
  {
    screen.pixels[i] = color;
  }
}

void update_pixels()
{
  SDL_UpdateTexture(texture, NULL, screen.pixels, screen.width * 4);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

int window_should_close()
{
  SDL_Event ev;
  if (SDL_PollEvent(&ev))
  {
    if (ev.type == SDL_QUIT)
    {
      return TRUE;
    }
  }

  return FALSE;
}

void quit_window()
{
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void draw_rect(int x, int y, int width, int height, uint32_t color)
{
  for (int i = x; i < x + width; i++)
  {
    for (int j = y; j < y + height; j++)
    {
      screen.pixels[j * screen.width + i] = color;
    }
  }
}