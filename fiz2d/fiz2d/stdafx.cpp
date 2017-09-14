#include "stdafx.h"

 Vector2 operator + (const  Vector2 &a, const  Vector2 &b) {
	return  Vector2(a.x + b.x, a.y + b.y);
}
 Vector2 operator - (const  Vector2 &a, const  Vector2 &b) {
	return  Vector2(a.x - b.x, a.y - b.y);
}
 Vector2 operator - (const  Vector2 &a) {
	return  Vector2(-a.x, -a.y);
}
 Vector2 operator * (const  Vector2 &a, const double b) {
	return  Vector2(a.x * b, a.y * b);
}
 Vector2 operator * (const double b, const  Vector2 &vec) {
	return  Vector2(vec.x * b, vec.y * b);
}
 Vector2 operator / (const  Vector2 &vec, const double b) {
	return Vector2(vec.x / b, vec.y / b);
}
Vector2 operator += (Vector2 &vec1, const Vector2 &vec2)
{
	return Vector2(vec1 = vec1+ vec2);
}
 Vector2 operator *= ( Vector2 &vec, const double b) {
	return  Vector2(vec = vec * b);
}
 Vector2 operator /= ( Vector2 &vec, const double b) {
	return  Vector2(vec = vec / b);
}