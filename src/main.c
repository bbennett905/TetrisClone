#include <stdlib.h>
#include <time.h>
#include "playfield.h"
#include "render.h"

int main(int argc, char* argv[])
{
	srand((unsigned)time(0));
	init_field();
	init_render();

	//todo:
	//input
	//game logic
	//graphics
	//audio
	
	//default descent rate should be 3/sec
	while (true)
	{
		render();
	}

	return 0;
}
