#include "input.h"

#include <SDL.h>
#include "playfield.h"

int quit = 0;
int down_pressed = 0;

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
}

int should_quit()
{
	return quit;
}

int should_drop_fast()
{
	return down_pressed;
}
