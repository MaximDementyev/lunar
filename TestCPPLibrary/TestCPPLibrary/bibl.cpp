#include "stdafx.h"
#include"function_header.h"

double norm(const struct Vector2 a, const struct Vector2 b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double norm(const struct Vector2* a, const struct Vector2* b) {
	return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}

double norm(const struct Vector2 a) {
	return sqrt(a.x*a.x + a.y*a.y);
}

double norm(const struct Vector2* a) {
	return sqrt(a->x * a->x + a->y * a->y);
}

double sign(const double a) {
	if (a > 0) return 1;
	if (a == 0) return 0;
	else return -1;
}

double dotprod(const struct Vector2 a, const struct Vector2 b) {
	return a.x * b.x + a.y * b.y;
}