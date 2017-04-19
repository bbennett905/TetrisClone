#include "render.h"

#include <SDL.h>
#include "playfield.h"

#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 540

SDL_Renderer* renderer;
SDL_Surface* screen_surface;
SDL_Window* window;

SDL_Rect NEXT_I_RECTS[] = { { 39, 50, 23, 23 },{ 39, 75, 23, 23 },
	{ 39, 100, 23, 23 }, { 39, 125, 23, 23 } };
SDL_Rect NEXT_L_RECTS[] = { { 25, 75, 23, 23 }, { 25, 100, 23, 23 },
	{ 25, 125, 23, 23 }, { 50, 125, 23, 23 } };
SDL_Rect NEXT_REVERSE_L_RECTS[] = { { 50, 75, 23, 23 }, { 50, 100, 23, 23 },
	{ 50, 125, 23, 23 }, { 25, 125, 23, 23 } };
SDL_Rect NEXT_SQUARE_RECTS[] = { { 25, 100, 23, 23 }, { 25, 125, 23, 23 },
	{ 50, 100, 23, 23 }, { 50, 125, 23, 23 } };
SDL_Rect NEXT_S_RECTS[] = { { 50, 75, 23, 23 }, { 50, 100, 23, 23 },
	{ 25, 100, 23, 23 }, { 25, 125, 23, 23 } };
SDL_Rect NEXT_REVERSE_S_RECTS[] = { { 25, 75, 23, 23 }, { 25, 100, 23, 23 },
	{ 50, 100, 23, 23 }, { 50, 125, 23, 23 } };
SDL_Rect NEXT_T_RECTS[] = { { 25, 75, 23, 23 }, { 50, 100, 23, 23 },
	{ 25, 100, 23, 23 }, { 25, 125, 23, 23 } };

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
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x99, 0x00, 0xFF);
		break;
	case COLOR_INDIGO:
		SDL_SetRenderDrawColor(renderer, 0x11, 0x00, 0xFF, 0xFF);
		break;
	case COLOR_YELLOW:
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
		break;
	case COLOR_GREEN:
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		break;
	case COLOR_RED:
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		break;
	case COLOR_MAGENTA:
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
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
	//Renders all stationary blocks as well as the active block
	for (int i = FIELD_SIZE - (2 * FIELD_WIDTH); i > 0; i--)
	{
		vec2d8_t pos = { i % FIELD_WIDTH, i / FIELD_WIDTH };
		SDL_Rect r = (SDL_Rect){(100 + 25 * pos.x), (20 + 25 * (20 - pos.y)), 23, 23 };
		set_draw_color(color_at(pos));
		SDL_RenderDrawRect(renderer, &r);
	}
}

void render_next()
{
	set_draw_color(get_next() + 1);
	//Top left for this will be at x=25, y=50
	//each block is 23x23, 1px border, etc
	switch (get_next())
	{
	case TETROMINO_I:
		SDL_RenderDrawRects(renderer, NEXT_I_RECTS, 4);
		break;
	case TETROMINO_L:
		SDL_RenderDrawRects(renderer, NEXT_L_RECTS, 4);
		break;
	case TETROMINO_REVERSE_L:
		SDL_RenderDrawRects(renderer, NEXT_REVERSE_L_RECTS, 4);
		break;
	case TETROMINO_SQUARE:
		SDL_RenderDrawRects(renderer, NEXT_SQUARE_RECTS, 4);
		break;
	case TETROMINO_S:
		SDL_RenderDrawRects(renderer, NEXT_S_RECTS, 4);
		break;
	case TETROMINO_REVERSE_S:
		SDL_RenderDrawRects(renderer, NEXT_REVERSE_S_RECTS, 4);
		break;
	case TETROMINO_T:
		SDL_RenderDrawRects(renderer, NEXT_T_RECTS, 4);
		break;
	}
}

void render()
{
	//each block is 23x23, 1px black border each side
	//so total playfield pixel width is 250, VISIBLE h is 500px
	// extra space on left must be 100px, 20px border elsewhere
	// final window w = 350 h = 540
	//TODO blit bg img;
	//TODO blit score
	render_next();
	render_field();

	SDL_RenderPresent(renderer);
}

void kill_render()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
