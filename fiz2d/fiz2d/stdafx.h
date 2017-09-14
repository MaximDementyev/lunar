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
#include "cmath"
#define _USE_MATH_DEFINES


 struct Vector2 {
	double x;
	double y;

	Vector2() { x = 0; y = 0; }
	Vector2(double nx, double ny) { x = nx, y = ny; }
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



 struct object {
	 Vector2 Coord;
	 Vector2 Velocity;
	 Vector2 Acceleration;
	 Vector2 Force;
};

 struct state_model {
	 object body;
	 object wheel;
};

/* state_model {
 Vector2 Coord;
 Vector2 Velocity;
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
	 Kwheel wheel;
	 Kbody body;
	 Kworld world;
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

 struct  runge_K {
	 koef1 kx1;
	 koef1 kx2;
};
