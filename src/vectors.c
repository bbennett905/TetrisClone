#include "vectors.h"

vec2d8_t mult(mat2d8_t mat, vec2d8_t vec)
{
	vec2d8_t res;
	res.x = vec.x * mat.m11 + vec.y * mat.m12;
	res.y = vec.x * mat.m21 + vec.y * mat.m22;
	return res;
}

vec2d8_t add(vec2d8_t vecA, vec2d8_t vecB)
{
	vecA.x += vecB.x;
	vecA.y += vecB.y;
	return vecA;
}

vec2d8_t sub(vec2d8_t vecA, vec2d8_t vecB)
{
	vecA.x -= vecB.x;
	vecA.y -= vecB.y;
	return vecA;
}
