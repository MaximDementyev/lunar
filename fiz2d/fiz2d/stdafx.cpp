#include "stdafx.h"

struct Vector2 operator + (const struct Vector2 &a, const struct Vector2 &b) {
	struct Vector2 res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}

struct Vector2 operator - (const struct Vector2 &a, const struct Vector2 &b) {
	struct Vector2 res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}

struct Vector2 operator - (const struct Vector2 &a) {
	struct Vector2 res;
	res.x = -a.x;
	res.y = -a.y;
	return res;
}

struct Vector2 operator * (const struct Vector2 &a, const double b) {
	struct Vector2 res;
	res.x = a.x * b;
	res.y = a.y * b;
	return res;
}

struct Vector2 operator * (const double b, const struct Vector2 &a) {
	struct Vector2 res;
	res.x = a.x * b;
	res.y = a.y * b;
	return res;
}

struct Vector2 operator / (struct Vector2 &a, const double b) {
	struct Vector2 res;
	if (b != 0) {
		res.x = a.x / b;
		res.y = a.y / b;
		return res;
	}
	return res;
}

struct Vector2 operator *= (struct Vector2 &a, const double b) {
	struct Vector2 res;
	res.x = a.x * b;
	res.y = a.y * b;
	return res;
}