#include <stdlib.h>
#include <time.h>
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
	//default descent rate should be 3/sec
	//will also probably want to cap at 30fps

	while (!should_quit())
	{
		handle_input();
		update_field();
		render();
		SDL_Delay(50);
	}

	return 0;
}
