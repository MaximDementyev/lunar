// stdafx.h: включаемый файл для cтандартных cиcтемных включаемых файлов
// или включаемых файлов для конкретного проекта, которые чаcто иcпользуютcя, но
// не чаcто изменяютcя

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Иcключите редко иcпользуемые компоненты из заголовков Windows
// Файлы заголовков Windows:
#include <windows.h>

// TODO: Уcтановите здеcь ccылки на дополнительные заголовки, требующиеcя для программы

#include "stdio.h"
#include "stdlib.h"
#define _USE_MATH_DEFINES
#include "cmath"



struct Vector2 {
	double x;
	double y;

	struct Vector2() { x = 0; y = 0; }
	struct Vector2(double nx, double ny) { x = nx, y = ny; }
	void set(double nx, double ny) { x = nx; y = ny; }
	void set(struct Vector2 vec) { x = vec.x, y = vec.y; }
	void set0() { x = y = 0; }

	friend struct Vector2 operator + (const struct Vector2 &, const struct Vector2 &);
	friend struct Vector2 operator - (const struct Vector2 &, const struct Vector2 &);
//	struct Vector2 operator - (const struct Vector2 &);
	friend struct Vector2 operator * (const struct Vector2 &, const double);
	friend struct Vector2 operator * (const double, const struct Vector2 &);
	friend struct Vector2 operator *= (struct Vector2 &, const double);
	friend struct Vector2 operator / (const struct Vector2 &, const double);
	friend struct Vector2 operator /= (struct Vector2 &, const double);
};



struct object {
	struct Vector2 Coord;
	struct Vector2 Velocity;
	struct Vector2 Acceleration;
	struct Vector2 Force;
};

struct state_model {
	struct object body;
	struct object wheel;
};

/*struct state_model {
struct Vector2 Coord;
struct Vector2 Velocity;
};*/

struct Kwheel {
	double mass;
	double radius;
	double position;
	double rigidity_suspension;
};

struct Kbody {
	double mass;
};

struct Kworld {
	double gravity;
};

struct koef_of_model {
	struct Kwheel wheel;
	struct Kbody body;
	struct Kworld world;
};

/*struct koef_of_model {
double mass;
double gravity;
double radius;
};*/

struct surface {
	double start_x;
	double start_y;
	double left_height;
	double right_height;
	double angle;
	double limitation_x;
	double mu;
};


//struct for runge koef
struct koef1 {
	struct Vector2 k1;
	struct Vector2 k2;
	struct Vector2 k3;
	struct Vector2 k4;
};

struct runge_K {
	struct koef1 kx1;
	struct koef1 kx2;
};
