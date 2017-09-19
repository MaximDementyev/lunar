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

object_wheel::object_wheel() {
	state_wheel.coord.set0();
	state_wheel.velocity.set0();
	state_wheel.acceleration.set0();
	state_wheel.force.set0();
	state_wheel.local_coord.set0();
	state_wheel.pitch = 0;

	//**
	k_wheel.mass = 0;
	k_wheel.leading = false;
	k_wheel.position = 0;
	k_wheel.radius = 0;
	k_wheel.rigidity_suspension = 0;
}

state_model::state_model() {
	body.state_body.coord.set0();
	body.state_body.velocity.set0();
	body.state_body.acceleration.set0();
	body.state_body.force.set0();
	body.state_body.pitch = 0;
	//
	body.k_body.mass = 0;

	//**
	wheel = nullptr;

	//**
	world.gravity = 0;
	
	//**
	number_wheel = 0;
}
