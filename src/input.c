#include "input.h"

#include <SDL.h>
#include "playfield.h"

#define FORCE_DESCEND_RATE 10 //number of blocks to drop/s
#define DEFAULT_DESCEND_RATE 2

int quit = 0;
int down_pressed = 0;
Uint32 last_drop_time = 0;

void handle_input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = 1;
			return;
		}
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				rotate_active_tetromino();
				break;
			case SDLK_LEFT:
				shift_active_tetromino(SHIFT_LEFT);
				break;
			case SDLK_RIGHT:
				shift_active_tetromino(SHIFT_RIGHT);
				break;
			case SDLK_DOWN:
				down_pressed = 1;
				break;
			}
		}
		if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				down_pressed = 0;
			}
		}
	}
	
	if (down_pressed)
	{
		if (SDL_GetTicks() - last_drop_time >= (1000 / FORCE_DESCEND_RATE))
		{
			descend_active_tetromino();
			last_drop_time = SDL_GetTicks();
		}
	}
	else
	{
		//TODO this is just a convenient place to do this.. for now 
		if (SDL_GetTicks() - last_drop_time >= (1000 / DEFAULT_DESCEND_RATE))
		{
			descend_active_tetromino();
			last_drop_time = SDL_GetTicks();
		}
	}
}

int should_quit()
{
	return quit;
}
