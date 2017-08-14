#include "stdafx.h"

struct Vector2 operator + (const struct Vector2 &a, const struct Vector2 &b) {
	return struct Vector2(a.x + b.x, a.y + b.y);
}
struct Vector2 operator - (const struct Vector2 &a, const struct Vector2 &b) {
	return struct Vector2(a.x - b.x, a.y - b.y);
}
struct Vector2 operator - (const struct Vector2 &a) {
	return struct Vector2(-a.x, -a.y);
}
struct Vector2 operator * (const struct Vector2 &a, const double b) {
	return struct Vector2(a.x * b, a.y * b);
}
struct Vector2 operator * (const double b, const struct Vector2 &vec) {
	return struct Vector2(vec.x * b, vec.y * b);
}
struct Vector2 operator / (const struct Vector2 &vec, const double b) {
	return Vector2(vec.x / b, vec.y / b);
}
struct Vector2 operator *= (struct Vector2 &vec, const double b) {
	return struct Vector2(vec = vec * b);
}
struct Vector2 operator /= (struct Vector2 &vec, const double b) {
	return struct Vector2(vec = vec / b);
}