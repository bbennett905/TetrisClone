#include "blocks.h"
#include "playfield.h"

const mat2d8_t cw_rotate = { 0, 1, -1, 0 };

void rotate(tetromino_t* block)
{
	tetromino_t copy = *block;
	for (int i = 0; i < 4; i++)
	{
		copy._blocks[i]._pos = mult(cw_rotate, copy._blocks[i]._pos);
	}
	
	//after rotating, move block pos so that top left is back in place
	vec2d8_t old_pos = copy._pos;
	vec2d8_t top_left = { FIELD_WIDTH, 0 };
	for (int i = 0; i < 4; i++)
	{
		//Least X, greatest Y
		if (copy._blocks[i]._pos.x < top_left.x) top_left.x = copy._blocks[i]._pos.x;
		if (copy._blocks[i]._pos.y > top_left.y) top_left.y = copy._blocks[i]._pos.y;
	}
	vec2d8_t diff = sub(old_pos, top_left);
	for (int i = 0; i < 4; i++)
	{
		copy._blocks[i]._pos = add(copy._blocks[i]._pos, diff); //TODO double check this
	}

	//Make sure the blocks arent overlapping with anything - if so abort
	for (int i = 0; i < 4; i++)
	{
		if (is_block_at(copy._blocks[i]._pos)) return;
		if (copy._blocks[i]._pos.x < 0 || copy._blocks[i]._pos.x >= FIELD_WIDTH) return;
		if (copy._blocks[i]._pos.y < 0 || copy._blocks[i]._pos.y >= FIELD_HEIGHT) return;
	}

	//Passed checks, so the block can be rotated
	*block = copy;
}

bool is_colliding(tetromino_t* block)
{
	return false;
}
