#pragma once
#include "stdafx.h"

//bibl.cpp
double norm(struct Vector2 a, struct Vector2 b);
double norm(struct Vector2 a);
double sign(double);
double cos_deg(double a);
double sin_deg(double a);
double tan_deg(double a);
double dotprod(struct Vector2 a, struct Vector2 b);

//runge.cpp
struct state_model next_step_N(struct state_model current_model, struct koef_of_model koef_model, struct surface current_surface, double force, double time, double limitation_x);
struct state_model next_step_no_N(struct state_model current_model, struct koef_of_model koef_model, double time);

//runge_func.cpp
struct Vector2 func_solve_acceleration(struct Vector2 Velocity, struct koef_of_model koef_model, double force, struct surface current_surface);
struct runge_K runge_koef(struct Vector2 solve_velocity, struct Vector2 solve_acceleration, struct koef_of_model koef_model, struct surface current_surface, double force, double h);
struct Vector2 solve_koef_coord(struct runge_K K);
struct Vector2 solve_koef_velocity(struct runge_K K);

//xz.cpp
double find_earth(state_model current_model, koef_of_model koef_model, surface current_surface); //-2 error! We fell through the texture //-1 Touching outside a known surface //Through how many will be touching
struct Vector2 hit(state_model current_model, koef_of_model koef_model, surface current_surface);
