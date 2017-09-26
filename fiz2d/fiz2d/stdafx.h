// stdafx.h: ���������� ���� ��� c���������� c�c������ ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ��c�� �c��������c�, ��
// �� ��c�� ��������c�

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �c������� ����� �c���������� ���������� �� ���������� Windows
// ����� ���������� Windows:
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
	 double attachment_point;
	 double fastening direction;
	 double zero_position;
	 double max_position;
	 double min_position;
	 double mass;
	 double radius;
	 double rigidity_suspension;
	 bool leading;
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
	 double pitch;
};
 struct state_wheel_object {
	 Vector2 loc_coord;
	 Vector2 global_coord;
	 Vector2 loc_vel;
	 Vector2 loc_acc;
 };

struct object_body {
	state_body_object state_body;
	koef_body k_body;
};
struct object_wheel {
	state_wheel_object state_wheel;
	koef_wheel k_wheel;
	object_wheel();
};

 struct state_model {
	 object_body body;
	 object_wheel *wheel;
	 int number_wheel;
	 koef_world world;
	 state_model();
};

//only state model without koef, spesial for runge
struct light_model {
	state_body_object body;
	state_wheel_object *wheel;
};


//struct fo surface
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
 struct  runge_koef_body {
	 Vector2 k1;
	 Vector2 k2;
	 Vector2 k3;
	 Vector2 k4;
};

 struct  runge_koef_wheel {
	 double k1;
	 double k2;
	 double k3;
	 double k4;
 };

