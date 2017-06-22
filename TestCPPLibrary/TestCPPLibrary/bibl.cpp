#include "stdafx.h"

double norm (const struct Vector2 &a, const struct Vector2 &b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double norm (const struct Vector2 *a, const struct Vector2 *b) {
	return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}

double norm (const struct Vector2 &a) {
	return sqrt(a.x*a.x + a.y*a.y);
}

double norm (const struct Vector2 *a) {
	return sqrt(a->x * a->x + a->y * a->y);
}

double sign (const double a) {
	if (a >= 0) return 1;
	else return -1;
}

double cos_deg (const double a) {
	return cos (a * M_PI / 180);
}

double sin_deg (const double a) {
	return sin (a * M_PI / 180);
}

double tan_deg (const double a) {
	return tan (a * M_PI / 180);
}

double dotprod (const struct Vector2 &a, const struct Vector2 &b) {
	return a.x * b.x + a.y * b.y;
}