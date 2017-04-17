#include "render.h"

#include <SDL.h>
#include "playfield.h"

#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 540

SDL_Renderer* renderer;
SDL_Surface* screen_surface;
SDL_Window* window;

void set_draw_color(block_color color)
{
	switch (color)
	{
	case COLOR_NONE:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		break;
	case COLOR_CYAN:
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
		break;
	case COLOR_ORANGE:
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x77, 0xFF);
		break;
	case COLOR_INDIGO:
		SDL_SetRenderDrawColor(renderer, 0x11, 0xDD, 0x00, 0xFF);
		break;
	case COLOR_YELLOW:
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
		break;
	case COLOR_GREEN:
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		break;
	case COLOR_RED:
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		break;
	case COLOR_MAGENTA:
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
		break;
	}
}

void init_render()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN,
		&window, &renderer);
	screen_surface = SDL_GetWindowSurface(window);
}

void render_field()
{
	//each block is 23x23, 1px black border each side
	//so total playfield pixel width is 250, VISIBLE h is 500px
	// extra space on left must be 100px, 20px border elsewhere
	// final window w = 350 h = 540
	//TODO blit bg img;
	//TODO blit score, next
	//TODO render active tetromino

	for (int i = FIELD_SIZE - (2 * FIELD_WIDTH); i > 0; i--)
	{
		vec2d8_t pos = { i % FIELD_WIDTH, i / FIELD_WIDTH };
		SDL_Rect r = (SDL_Rect){(100 + 25 * pos.x), (20 + 25 * (20 - pos.y)), 23, 23 };
		set_draw_color(color_at(pos));
		SDL_RenderDrawRect(renderer, &r);
	}
}

void kill_render()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
