#include "playfield.h"

#include <stdlib.h>

#define FIELD_HEIGHT 22
#define FIELD_WIDTH 10
#define FIELD_SIZE (FIELD_HEIGHT * FIELD_WIDTH)

//only really need to save the color of each block, not its position
block_color field[FIELD_SIZE];

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
