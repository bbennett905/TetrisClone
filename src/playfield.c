#include "playfield.h"

#include <stdlib.h>

//only really need to save the color of each block, not its position
block_color field[FIELD_SIZE];
tetromino_t* active_tetromino;
tetromino_shape next;

void init_field()
{
	next = rand() % NUM_TETROMINO_SHAPES;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		field[i] = COLOR_NONE;
	}
}

bool is_block_at(vec2d8_t pos)
{
	return field[(pos.x * pos.y) - 1] != COLOR_NONE;
}

block_color color_at(vec2d8_t pos)
{
	if (field[(pos.x * pos.y) - 1] != COLOR_NONE)
		return field[(pos.x * pos.y) - 1];
	else
	{
		//Check to see if any active block is here
		for (int i = 0; i < 4; i++)
		{
			vec2d8_t p = add(active_tetromino->_blocks[i]._pos, active_tetromino->_pos);
			if (pos.x == p.x && pos.y == p.y)
			{
				return active_tetromino->_blocks[i]._color;
			}
		}
	}
	return COLOR_NONE;
}

tetromino_shape get_next()
{
	return next;
}

void kill_active_tetromino()
{
	for (int i = 0; i < 4; i++)
	{
		vec2d8_t temp_pos = add(active_tetromino->_pos, active_tetromino->_blocks[i]._pos);
		uint8_t field_pos = temp_pos.y * FIELD_WIDTH + temp_pos.x;
		field[field_pos] = active_tetromino->_blocks[i]._color;
	}
	free(active_tetromino);
	active_tetromino = NULL;
}

void spawn_tetromino()
{
	//make sure to srand((unsigned) time(time_t* t)) in main or something
	//This is random enough for this purpose
	tetromino_shape shape = next;
	next = rand() % NUM_TETROMINO_SHAPES;
	tetromino_t* t = (tetromino_t*)malloc(sizeof(tetromino_t));
	
	for (int i = 0; i < 4; i++)
	{
		t->_blocks[i]._color = shape + 1;
	}

	//Default spawn position
	t->_pos.x = 3;
	t->_pos.y = 21;

	switch (shape)
	{
	case TETROMINO_I:
		//Altered spawn position
		t->_pos.y = 20;
		
		t->_blocks[0]._pos = (vec2d8_t) { 0, 0 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[0]._pos = (vec2d8_t) { 2, 0 };
		t->_blocks[0]._pos = (vec2d8_t) { 3, 0 };
		break;
	case TETROMINO_L:
		t->_blocks[0]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 2, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 2, 0 };
		break;
	case TETROMINO_REVERSE_L:
		t->_blocks[0]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 2, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 0, 0 };
		break;
	case TETROMINO_SQUARE:
		//Altered spawn position
		t->_pos.x = 4;

		t->_blocks[0]._pos = (vec2d8_t) { 0, 0 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[0]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, -1 };
		break;
	case TETROMINO_S:
		t->_blocks[0]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[0]._pos = (vec2d8_t) { 2, 0 };
		break;
	case TETROMINO_REVERSE_S:
		t->_blocks[0]._pos = (vec2d8_t) { 0, 0 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[0]._pos = (vec2d8_t) { 2, -1 };
		break;
	case TETROMINO_T:
		t->_blocks[0]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[0]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[0]._pos = (vec2d8_t) { 2, -1 };
		break;
	}
	active_tetromino = t;
}

void descend_active_tetromino()
{
	active_tetromino->_pos.y -= 1;
}
