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

Vector2 &operator + (Vector2 a, Vector2 b) {
	Vector2 res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}

Vector2 &operator - (Vector2 a, Vector2 b) {
	Vector2 res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}

Vector2 &operator * (Vector2 a, double b) {
	Vector2 res;
	res.x = a.x * b;
	res.y = a.y * b;
	return res;
}

Vector2 &operator * (double b, Vector2 a) {
	Vector2 res;
	res.x = a.x * b;
	res.y = a.y * b;
	return res;
}

Vector2 &operator / (Vector2 a, double b) {
	Vector2 res;
	if (b != 0) {
		res.x = a.x / b;
		res.y = a.y / b;
		return res;
	}
	return res;
}

struct state_model {
	Vector2 Coord;
	Vector2 Velocity;
};

struct data_model {
	state_model state_model;
	bool flag_map;
};

struct koef_of_model {
	double mass;
	double gravity;
	double force;
};


//struct for runge koef
struct koef1 {
	Vector2 k1;
	Vector2 k2;
	Vector2 k3;
	Vector2 k4;
};

struct runge_K {
	koef1 kx1;
	koef1 kx2;
	koef1 kx3;
};