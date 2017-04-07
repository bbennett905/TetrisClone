#include "blocks.h"
#include "playfield.h"

const mat2d8_t cw_rotate = { 0, 1, -1, 0 };

void rotate(tetromino_t* block)
{
	//first need to check if it can be rotated without colliding with something
	//make a copy, and rotate that - check each block for collision with global
	tetromino_t copy = *block;
	for (int i = 0; i < 4; i++)
	{
		copy._blocks[i]._pos = mult(cw_rotate, copy._blocks[i]._pos);
	}
	
	//after rotating, move block pos so that top left is back in place
	//TODO

	for (int i = 0; i < 4; i++)
	{
		if (is_block_at(copy._blocks[i]._pos)) return;
		if (copy._blocks[i]._pos.x < 0 || copy._blocks[i]._pos.x >= FIELD_WIDTH) return;
		if (copy._blocks[i]._pos.y < 0 || copy._blocks[i]._pos.y >= FIELD_HEIGHT) return;
	}
	//Passed checks, so the block can be rotated
	//TODO


}

bool is_colliding(tetromino_t* block)
{
	return false;
}
