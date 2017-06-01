#pragma once
#include "stdafx.h"

//bibl.cpp
double norm(struct Vector2 a, struct Vector2 b);
double norm(struct Vector2 a);
double sign(double);
double cos_deg(double a);
double sin_deg(double a);
double tan_deg(double a);

//runge_func.cpp
struct Vector2 func_solve_acceleration(struct Vector2 Velocity, struct koef_of_model koef_model, double force, struct surface current_surface);
struct runge_K runge_koef(struct Vector2 solve_velocity, struct Vector2 solve_acceleration, struct koef_of_model koef_model, struct surface current_surface, double force, double h);
struct Vector2 solve_koef_coord(struct runge_K K);
struct Vector2 solve_koef_velocity(struct runge_K K);

//xz.cpp
double find_earth(state_model current_model, koef_of_model koef_model, surface current_surface);
