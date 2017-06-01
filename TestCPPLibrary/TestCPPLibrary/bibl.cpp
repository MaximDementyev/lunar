#include "stdafx.h"

double norm(struct Vector2 a, struct Vector2 b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double norm(struct Vector2 a) {
	return sqrt(a.x*a.x + a.y*a.y);
}

double sign(double a) {
	if (a > 0) return 1;
	if (a == 0) return 0;
	else return -1;
}

double cos_deg(double a) {
	return cos(a * M_PI / 180);
}

double sin_deg(double a) {
	return sin(a * M_PI / 180);
}

double tan_deg(double a) {
	return tan(a * M_PI / 180);
}