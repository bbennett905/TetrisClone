#include "playfield.h"
#include "input.h"
#include "SDL.h"

#include <stdlib.h>

#define FORCE_DESCEND_RATE 10 //number of blocks to drop/s
#define DEFAULT_DESCEND_RATE 2

//only really need to save the color of each block, not its position
block_color field[FIELD_SIZE];
tetromino_t* active_tetromino;
tetromino_shape next;
Uint32 last_drop_time = 0;

void init_field()
{
	next = rand() % NUM_TETROMINO_SHAPES;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		field[i] = COLOR_NONE;
	}
}

void row_complete_check()
{
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		int has_empty_spot = 0;
		for (int j = 0; j < FIELD_WIDTH; j++)
		{
			if (!is_block_at((vec2d8_t) { j, i } ))
			{ 
				has_empty_spot = 1;
				break;
			}
		}
		if (!has_empty_spot)
		{
			//TODO Score
			//Clear row, then drop all blocks above it down 1
			for (int j = 0; j < FIELD_WIDTH; j++)
			{
				field[(j + i * FIELD_WIDTH)] = COLOR_NONE;
			}
			for (int j = i + 1; j < FIELD_HEIGHT; j++)
			{
				for (int k = 0; k < FIELD_WIDTH; k++)
				{
					block_color col = color_at((vec2d8_t) { k, j });
					if (col != COLOR_NONE)
					{
						field[k + (j - 1) * FIELD_WIDTH] = col;
						field[k + j * FIELD_WIDTH] = COLOR_NONE;
					}
				}
			}
			i--;
		}
	}
}

void update_field()
{
	int should_stop = 0;
	for (int i = 0; i < 4; i++)
	{
		vec2d8_t y_1 = { 0, 1 };
		if ((active_tetromino->_blocks[i]._pos.y + active_tetromino->_pos.y) <= 0 ||
			is_block_at(sub(add(active_tetromino->_blocks[i]._pos, active_tetromino->_pos), y_1)))
		{
			should_stop = 1;
		}
	}
	if (should_stop)
	{
		if (SDL_GetTicks() - last_drop_time >= (1000 / DEFAULT_DESCEND_RATE))
		{
			kill_active_tetromino();
			row_complete_check();
			//TODO check for loss
			spawn_tetromino();
		}
		return;
	}

	if (should_drop_fast())
	{
		if (SDL_GetTicks() - last_drop_time >= (1000 / FORCE_DESCEND_RATE))
		{
			descend_active_tetromino();
			last_drop_time = SDL_GetTicks();
		}
	}
	else
	{
		if (SDL_GetTicks() - last_drop_time >= (1000 / DEFAULT_DESCEND_RATE))
		{
			descend_active_tetromino();
			last_drop_time = SDL_GetTicks();
		}
	}
}

int is_block_at(vec2d8_t pos)
{
	return field[(pos.x + pos.y * FIELD_WIDTH)] != COLOR_NONE;
}

block_color color_at(vec2d8_t pos)
{
	if (field[(pos.x + pos.y * FIELD_WIDTH)] != COLOR_NONE)
		return field[(pos.x + pos.y * FIELD_WIDTH)];
	else
	{
		if (active_tetromino)
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
	}
	return COLOR_NONE;
}

tetromino_shape get_next()
{
	return next;
}

void kill_active_tetromino()
{
	if (!active_tetromino) return;
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
		t->_blocks[1]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[2]._pos = (vec2d8_t) { 2, 0 };
		t->_blocks[3]._pos = (vec2d8_t) { 3, 0 };
		break;
	case TETROMINO_L:
		t->_blocks[0]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[1]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[2]._pos = (vec2d8_t) { 2, -1 };
		t->_blocks[3]._pos = (vec2d8_t) { 2, 0 };
		break;
	case TETROMINO_REVERSE_L:
		t->_blocks[0]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[1]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[2]._pos = (vec2d8_t) { 2, -1 };
		t->_blocks[3]._pos = (vec2d8_t) { 0, 0 };
		break;
	case TETROMINO_SQUARE:
		//Altered spawn position
		t->_pos.x = 4;

		t->_blocks[0]._pos = (vec2d8_t) { 0, 0 };
		t->_blocks[1]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[2]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[3]._pos = (vec2d8_t) { 1, -1 };
		break;
	case TETROMINO_S:
		t->_blocks[0]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[1]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[2]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[3]._pos = (vec2d8_t) { 2, 0 };
		break;
	case TETROMINO_REVERSE_S:
		t->_blocks[0]._pos = (vec2d8_t) { 0, 0 };
		t->_blocks[1]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[2]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[3]._pos = (vec2d8_t) { 2, -1 };
		break;
	case TETROMINO_T:
		t->_blocks[0]._pos = (vec2d8_t) { 0, -1 };
		t->_blocks[1]._pos = (vec2d8_t) { 1, -1 };
		t->_blocks[2]._pos = (vec2d8_t) { 1, 0 };
		t->_blocks[3]._pos = (vec2d8_t) { 2, -1 };
		break;
	}
	active_tetromino = t;
}

void descend_active_tetromino()
{
	if (!active_tetromino) return;
	active_tetromino->_pos.y -= 1;
}

void rotate_active_tetromino()
{
	if (!active_tetromino) return;
	rotate(active_tetromino);
}

void shift_active_tetromino(shift_direction dir)
{
	if (!active_tetromino) return;
	tetromino_t copy = *active_tetromino;
	
	if (dir == SHIFT_LEFT)
		copy._pos.x -= 1;
	if (dir == SHIFT_RIGHT && copy._pos.x < FIELD_WIDTH - 1)
		copy._pos.x += 1;

	for (int i = 0; i < 4; i++)
	{
		if (is_block_at(add(copy._blocks[i]._pos, copy._pos))) return;
		if (copy._pos.x + copy._blocks[i]._pos.x < 0) return;
		if (copy._pos.x + copy._blocks[i]._pos.x >= FIELD_WIDTH) return;
	}
	*active_tetromino = copy;
}
