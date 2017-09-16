// stdafx.h: включаемый файл для cтандартных cиcтемных включаемых файлов
// или включаемых файлов для конкретного проекта, которые чаcто иcпользуютcя, но
// не чаcто изменяютcя

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Иcключите редко иcпользуемые компоненты из заголовков Windows
// Файлы заголовков Windows:
#include <windows.h>
#include "stdio.h"
#include "stdlib.h"
#include "cmath"
#define _USE_MATH_DEFINES


 struct Vector2 {
	double x;
	double y;
	//\//
	Vector2() { x = 0; y = 0; }
	Vector2(double nx, double ny) { x = nx, y = ny; }
	~Vector2() { x = 0; y = 0; }

	void set(double nx, double ny) { x = nx; y = ny; }
	void set( Vector2 vec) { x = vec.x, y = vec.y; }
	void set0() { x = y = 0; }

	friend  Vector2 operator + (const  Vector2 &, const  Vector2 &);
	friend  Vector2 operator - (const  Vector2 &, const  Vector2 &);
//	 Vector2 operator - (const  Vector2 &);
	friend  Vector2 operator * (const  Vector2 &, const double);
	friend  Vector2 operator * (const double, const  Vector2 &);
	friend  Vector2 operator / (const  Vector2 &, const double);
	friend  Vector2 operator += ( Vector2 &, const  Vector2 &);
	friend  Vector2 operator *= ( Vector2 &, const double);
	friend  Vector2 operator /= ( Vector2 &, const double);
 };


 struct koef_wheel {
	 double mass;
	 double radius;
	 double position;
	 double rigidity_suspension;
 };

 struct koef_body {
	 double mass;
 };

 struct koef_world {
	 double gravity;
 };

 struct state_body_object {
	 Vector2 coord;
	 Vector2 velocity;
	 Vector2 acceleration;
	 Vector2 force;
	 double pitch;
};
 struct state_wheel_object {
	 Vector2 coord;
	 Vector2 local_coord;
	 Vector2 velocity;
	 Vector2 acceleration;
	 Vector2 force;
	 double pitch;
 };

struct object_body {
	state_body_object state_body;
	koef_body k_body;
};
struct object_wheel {
	state_wheel_object state_wheel;
	koef_wheel k_wheel;
};

 struct state_model {
	 object_body body;
	 object_wheel *wheel;
	 int number_wheel;
	 koef_world world;
};



 struct  surface {
	double start_x;
	double start_y;
	double left_height;
	double right_height;
	double angle;
	double limitation_x;
	double mu;
};


// for runge koef
 struct  koef1 {
	 Vector2 k1;
	 Vector2 k2;
	 Vector2 k3;
	 Vector2 k4;
};


