// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // »сключите редко используемые компоненты из заголовков Windows
// ‘айлы заголовков Windows:
#include <windows.h>

// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы

#include"function_header.h"

#include "stdio.h"
#include "stdlib.h"
#define _USE_MATH_DEFINES
#include "cmath"



struct Vector2 {
	double x = 0;
	double y = 0;
};

struct Vector2 operator + (const struct Vector2 &, const struct Vector2 &);
struct Vector2 operator - (const struct Vector2 &, const struct Vector2 &);
struct Vector2 operator - (const struct Vector2 &);
struct Vector2 operator * (const struct Vector2 &, const double);
struct Vector2 operator * (const double, const struct Vector2 &);
struct Vector2 operator *= (struct Vector2 &, const double);
struct Vector2 operator / (struct Vector2 &, const double);


struct state_model {
	struct Vector2 Coord;
	struct Vector2 Velocity;
};

/*struct data_model {
	struct state_model state_model;
	int flag_map;
	double time_left;
};*/

struct koef_of_model {
	double mass;
	double gravity;
	double radius;
};

struct surface {
	double start_x;
	double srart_y;
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
	struct koef1 kx3;
};