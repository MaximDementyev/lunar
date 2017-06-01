#include "stdafx.h"

struct Vector2 &operator + (struct Vector2 a, struct Vector2 b) {
	struct Vector2 res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}

struct Vector2 &operator - (struct Vector2 a, struct Vector2 b) {
	struct Vector2 res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}

struct Vector2 &operator * (struct Vector2 a, double b) {
	struct Vector2 res;
	res.x = a.x * b;
	res.y = a.y * b;
	return res;
}

struct Vector2 &operator * (double b, struct Vector2 a) {
	struct Vector2 res;
	res.x = a.x * b;
	res.y = a.y * b;
	return res;
}

struct Vector2 &operator / (struct Vector2 a, double b) {
	struct Vector2 res;
	if (b != 0) {
		res.x = a.x / b;
		res.y = a.y / b;
		return res;
	}
	return res;
}
