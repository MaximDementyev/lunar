#pragma once
#include "stdafx.h"

//bibl.cpp
double norm(Vector2 a, Vector2 b);
double norm(Vector2 a);
double sign(double);
double cos_deg(double a);
double sin_deg(double a);

//runge_func.cpp
Vector2 func_solve_acceleration(Vector2 Velocity, koef_of_model koef_model, double alpha, double mu);
runge_K runge_koef(Vector2 solve_velocity, Vector2 solve_acceleration, double h, koef_of_model koef_model, double alpha, double mu);
Vector2 solve_koef_coord(runge_K K);
Vector2 solve_koef_velocity(runge_K K);