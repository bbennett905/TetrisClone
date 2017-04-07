#pragma once

typedef struct vec2d8_t
{
	char x;
	char y;
} vec2d8_t;

typedef struct mat2d8_t
{
	char m11;
	char m12;
	char m21;
	char m22;
} mat2d8_t;

vec2d8_t mult(mat2d8_t mat, vec2d8_t vec);
vec2d8_t add(vec2d8_t vecA, vec2d8_t vecB);
vec2d8_t sub(vec2d8_t vecA, vec2d8_t vecB);
