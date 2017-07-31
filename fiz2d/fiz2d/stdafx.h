// stdafx.h: ���������� ���� ��� c���������� c�c������ ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ��c�� �c��������c�, ��
// �� ��c�� ��������c�

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �c������� ����� �c���������� ���������� �� ���������� Windows
// ����� ���������� Windows:
#include <windows.h>

// TODO: �c�������� ���c� cc���� �� �������������� ���������, ���������c� ��� ���������

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

struct koef_of_model {
	double mass;
	double gravity;
	double radius;
};

struct surface {
	double start_x;
	double start_y;
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