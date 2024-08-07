#include "lemonic.h"

/* data */
static screen_t screen;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;

static float delta_time;
static float last_frame_time;

static int n_letters = 7;
static int alphabet[][FONT_SIZE] = {
    {
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
    },	
    {
	0,0,1,0,0,
	0,1,0,1,0,
	1,0,0,0,1,
	1,1,1,1,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
    },
    {
	1,1,1,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
	1,1,1,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
	1,1,1,1,0,
    },
    {
	0,1,1,1,0,
	1,0,0,0,1,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,1,
	0,1,1,1,0,
    },
    {
	1,1,1,0,0,
	1,0,0,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,1,0,
	1,1,1,0,0,
    },
    {
	1,1,1,1,1,
	1,0,0,0,0,
	1,0,0,0,0,
	1,1,1,1,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,1,1,1,1,
    },
    {
	1,1,1,1,1,
	1,0,0,0,0,
	1,0,0,0,0,
	1,1,1,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
    },
    {
	0,1,1,1,0,
	1,0,0,0,1,
	1,0,0,0,0,
	1,0,0,1,1,
	1,0,0,0,1,
	1,0,0,0,1,
	0,1,1,1,0,
    },
    {
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,1,1,1,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
    },
    {
	0,1,1,1,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,1,1,1,0,
    },
    {
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,1,
	0,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	0,1,1,1,0,
    },
    {
	1,0,0,0,1,
	1,0,0,1,0,
	1,0,1,0,0,
	1,1,0,0,0,
	1,0,1,0,0,
	1,0,0,1,0,
	1,0,0,0,1,
    },
    {
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,1,1,1,1,
    },
    {
	1,0,0,0,1,
	1,1,0,1,1,
	1,0,1,0,1,
	1,0,1,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
    },
    {
	1,1,0,0,1,
	1,1,0,0,1,
	1,0,1,0,1,
	1,0,1,0,1,
	1,0,0,1,1,
	1,0,0,1,1,
	1,0,0,0,1,
    },
    {
	0,1,1,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	0,1,1,1,0,
    },
    {
	1,1,1,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
	1,1,1,1,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
    },
    {
	0,1,1,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,1,0,1,
	1,0,0,1,0,
	0,1,1,0,1,
    },
    {
	1,1,1,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
	1,1,1,1,0,
	1,0,0,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
    },
    {
	0,1,1,1,0,
	1,0,0,0,1,
	1,0,0,0,0,
	0,1,1,1,0,
	0,0,0,0,1,
	1,0,0,0,1,
	0,1,1,1,0,
    },
    {
	1,1,1,1,1,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
    },
    {
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	0,1,1,1,0,
    },
    {
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	0,1,0,1,0,
	0,1,0,1,0,
	0,0,1,0,0,
    },
    {
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,1,0,1,
	1,0,1,0,1,
	0,1,0,1,0,
	0,1,0,1,0,
    },
    {
	1,0,0,0,1,
	1,0,0,0,1,
	0,1,0,1,0,
	0,0,1,0,0,
	0,1,0,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
    },
    {
	1,0,0,0,1,
	1,0,0,0,1,
	0,1,0,1,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
    },
    {
	1,1,1,1,1,
	0,0,0,0,1,
	0,0,0,1,0,
	0,0,1,0,0,
	0,1,0,0,0,
	1,0,0,0,0,
	1,1,1,1,1,
    },
};

void init_window(int width, int height, char* title, int scale, uint32_t color)
{ 
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * scale, height * scale, 0);  
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);

    screen.width = width;
    screen.height = height;
    screen.pixels = (uint32_t*)malloc(screen.width * screen.height * sizeof(uint32_t));

    for (int i = 0; i < screen.width * screen.height; i++)
    {
        screen.pixels[i] = color;
    }
}

void update_dt()
{
    /* get the delta time */
    delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    int delay = TARGET_FRAME_TIME - (SDL_GetTicks() - last_frame_time); 

    if (delay > 0 && delay <= TARGET_FRAME_TIME)
    {
        SDL_Delay(delay);
    }

    /* update the last frame time to calculate stuff again */
    last_frame_time = SDL_GetTicks();
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
    free(screen.pixels);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_pixel(int x, int y, uint32_t color)
{
    if (x >= 0 && x < screen.width &&
        y >= 0 && y < screen.height)
    {
        screen.pixels[y * screen.width + x] = color;
    }
}

void fill_rect(int x, int y, int width, int height, uint32_t color)
{
    for (int i = x; i < x + width; i++)
    {
        for (int j = y; j < y + height; j++)
        {
            draw_pixel(i, j, color);
        }
    }
}

void draw_line(int x1, int y1, int x2, int y2, uint32_t color)
{
    int dx = MAX(x1, x2) - MIN(x1, x2);
    int dy = MAX(y1, y2) - MIN(y1, y2);
	
    int slope = (ABS(dx) > ABS(dy)) ? ABS(dx) : ABS(dy);

    float x_step = (float)dx / (float)slope;
    float y_step = (float)dy / (float)slope;
    
    float x = MIN(x1, x2);
    float y = MIN(y1, y2);

    for (int i = 0; i <= slope; i++)
    {
	draw_pixel(x, y, color);

	x += x_step;
	y += y_step;
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color)
{
    draw_line(x, y, x + width, y, color);
    draw_line(x, y, x, y + height, color);
    draw_line(x + width, y, x + width, y + height, color);
    draw_line(x, y + height, x + width, y + height, color);
    draw_pixel(x + width, y + height, color);
}

void draw_circle(int x, int y, int r, uint32_t color)
{
    float ang = 0;
    
    for (int i = 0; i < 2 * PI * r; i++)
    {
        ang += PI / (PI * r);
        float xx = cos(ang) * r;
        float yy = sin(ang) * r;
        
        draw_pixel(x + (int)xx, y + (int)yy, color);
    }
}

void fill_circle(int x, int y, int r, uint32_t color)
{
    float ang = 0;

    for (int i = 0; i < 2 * PI * r; i++)
    {
        ang += PI / (PI * r);
        float xx = cos(ang) * r;
        float yy = sin(ang) * r;

        for (int j = y - yy + 1; j < y + yy - 1; j++)
        {
            draw_line(x + (int)xx, j, x - (int)xx, j, color);
        }
    }   
}

void clear_screen(uint32_t color)
{
    for (int i = 0; i < screen.width * screen.height; i++)
    {
        screen.pixels[i] = color;
    }
}

int is_key_down(int key)
{
    const uint8_t* state = SDL_GetKeyboardState(NULL);  

    if (state[key + 4]) 
    {
        return TRUE;
    }

    return FALSE;
}

sprite_t load_ppm(char* path)
{
    sprite_t spr;

    FILE* file = fopen(path, "r");

    char format[2];
    fscanf(file, "%s\n", format);
    if (strcmp(format, "P6") == 0)
    {
        fscanf(file, "%d %d\n", &spr.width, &spr.height);

        int blah;
        fscanf(file, "%d\n", &blah);

        spr.pixels = (uint32_t*)malloc(spr.width * spr.height * sizeof(uint32_t));

        for (int i = 0; i < spr.width * spr.height; i++)
        {
            uint8_t r, g, b;
            fread(&r, 1, 1, file);
            fread(&g, 1, 1, file);
            fread(&b, 1, 1, file);

            spr.pixels[i] = (r << 16) | (g << 8) | b;
        }
    }

    fclose(file);
    return spr;
}

void draw_sprite(sprite_t spr, int x, int y)
{
    for (int i = 0; i < spr.width; i++)
    {
        for (int j = 0; j < spr.height; j++)
        {
            draw_pixel(x + i, y + j, spr.pixels[j * spr.width + i]);
        }
    }
}

int point_vs_rect(vec2_t v, rect_t r)
{
    return (v.x >= r.x && v.x <= r.x + r.width &&
            v.y >= r.y && v.y <= r.y + r.height);
}

int rect_vs_rect(rect_t r1, rect_t r2)
{
    if (r1.x + r1.width >= r2.x && r1.x <= r2.x + r2.width &&
        r1.y + r1.height >= r2.y && r1.y <= r2.y + r2.height)
    {
        return TRUE;
    }
    return FALSE;
}

int is_letter(char c)
{
    return (c >= 'a' && c <= 'z');
}

int get_letter_from_char(char c)
{
    if (is_letter(c))
    {
	return c - 'a' + 1;
    }

    return 0;
}

void draw_text(const char* text, int length, int x, int y, uint32_t color)
{
    int xx = 0;
    for (int c = 0; c < length; c++)
    {
	int letter = get_letter_from_char(text[c]);
	for (int i = 0; i < FONT_WIDTH; i++)
	{
	    for (int j = 0; j < FONT_HEIGHT; j++)
	    {
		int current_pixel = alphabet[letter][j * FONT_WIDTH + i];

		if (current_pixel)
		{
		    draw_pixel(x + i + xx, y + j, current_pixel);
		}
	    }
	}

	xx += FONT_WIDTH + 1;
    }
}
