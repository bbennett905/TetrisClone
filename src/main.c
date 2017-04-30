#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "playfield.h"
#include "render.h"
#include "input.h"

int main(int argc, char* argv[])
{
	srand((unsigned)time(0));
	init_field();
	init_render();

	//todo:
	//game logic
	//audio
	spawn_tetromino();

	while (!should_quit() && !has_lost())
	{
		handle_input();
		update_field();
		render();
		SDL_Delay(50);
	}
	kill_render();
	printf("You lost! Better luck next time :(");
	SDL_Delay(3000);
	return 0;
}
