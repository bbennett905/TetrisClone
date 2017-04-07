#pragma once

#include "blocks.h"
#include "vectors.h"
#include "types.h"

void init_field();
bool is_block_at(vec2d8_t pos);
block_color color_at(vec2d8_t pos);
