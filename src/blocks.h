#pragma once
#include "types.h"
#include "vectors.h"

typedef enum block_color
{
	COLOR_NONE,
	COLOR_CYAN,
	COLOR_ORANGE,
	COLOR_INDIGO,
	COLOR_YELLOW,
	COLOR_GREEN,
	COLOR_RED,
	COLOR_MAGENTA,
	NUM_BLOCK_COLORS
} block_color;

//Blocks make up a tetromino - position is relative to tetromino
typedef struct block_t
{
	//default tetris field is 10x20, can use a few hidden extra at the top to spawn blocks in
	//If a block is accessed as part of a tetromino, these positions are relative
	vec2d8_t _pos;

	block_color _color;

	// _is_active //or, just have 1 global block_t* active_block
} block_t;

typedef enum tetromino_shape
{
	TETROMINO_I,
	TETROMINO_L,
	TETROMINO_REVERSE_L,
	TETROMINO_SQUARE,
	TETROMINO_S,
	TETROMINO_REVERSE_S,
	TETROMINO_T,
	NUM_TETROMINO_SHAPES
} tetromino_shape;

/*typedef enum tetromino_rotation
{
	ROTATION_NONE,
	ROTATION_90,
	ROTATION_180,
	ROTATION_270,
	NUM_ROTATIONS
} tetromino_rotation;*/

typedef struct tetromino_t
{
	//Position of the top left block, if you treat the tetromino as a filled rectangle
	vec2d8_t _pos;

	//tetromino_shape _shape;
	//tetromino_rotation _rotation; //This may be unnecessary, using relative block pos
	//Tetrominos always have 4 blocks, hence the name
	block_t _blocks[4];
} tetromino_t;

//Attempts to rotate a tetromino 90 degrees CW
void rotate(tetromino_t* block);

//Returns true if a block is under the tetromino
bool has_block_under(tetromino_t* block);
