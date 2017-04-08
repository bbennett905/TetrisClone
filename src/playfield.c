#include "playfield.h"

#include <stdlib.h>

//only really need to save the color of each block, not its position
block_color field[FIELD_SIZE];
tetromino_t* active_tetromino;

void init_field()
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		field[i] = COLOR_NONE;
	}
}

bool is_block_at(vec2d8_t pos)
{
	return color_at(pos) != COLOR_NONE;
}

block_color color_at(vec2d8_t pos)
{
	return field[(pos.x * pos.y) - 1];
}
