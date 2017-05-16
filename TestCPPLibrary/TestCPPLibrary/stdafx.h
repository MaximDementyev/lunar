// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
#include <windows.h>

// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������

#include "stdio.h"
#include "stdlib.h"


struct Vector2 {
	double x;
	double y;
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

struct state_model {
	Vector2 Coord;
	Vector2 Velocity;
};

struct data {
	Vector2 Vector2;
	bool flag_map;
};

struct koef_of_model {
	double mass;
	double gravity;
	double force;
};