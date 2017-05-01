#pragma once

#include "blocks.h"
#include "vectors.h"
#include "types.h"

#define FIELD_HEIGHT 22
#define FIELD_WIDTH 10
#define FIELD_SIZE (FIELD_HEIGHT * FIELD_WIDTH)

typedef enum shift_direction
{
	SHIFT_LEFT,
	SHIFT_RIGHT
} shift_direction;

//Initialize the playfield
void init_field();
//Update playfield
void update_field();
//Returns true if there is a block at this field position
int is_block_at(vec2d8_t pos);
//Returns the color of a block at this position
block_color color_at(vec2d8_t pos);
//Returns the shape of the next tetromino
tetromino_shape get_next();
//Kills the currently active tetromino and updates the field blocks; frees the tetromino
void kill_active_tetromino();
//Spawns a random new tetromino and sets it as active
void spawn_tetromino();
//Moves the active tetromino down by one unit
void descend_active_tetromino();
//Rotates the active tetromino
void rotate_active_tetromino();
void shift_active_tetromino(shift_direction dir);
int has_lost();
int get_lines_cleared();
