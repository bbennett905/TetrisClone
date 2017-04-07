#include "blocks.h"

void rotate(tetromino_t* block)
{
	//first need to check if it can be rotated without colliding with something
	//make a copy, and rotate that - check each block for collision with global
	tetromino_t copy = *block;
	//after rotating, move block pos so that top left is back in place
}

bool is_colliding(tetromino_t* block)
{
	return false;
}
