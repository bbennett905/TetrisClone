#pragma once

#include "blocks.h"
#include "vectors.h"
#include "types.h"

#define FIELD_HEIGHT 22
#define FIELD_WIDTH 10
#define FIELD_SIZE (FIELD_HEIGHT * FIELD_WIDTH)

void init_field();
bool is_block_at(vec2d8_t pos);
block_color color_at(vec2d8_t pos);
void kill_active_tetromino();
void
