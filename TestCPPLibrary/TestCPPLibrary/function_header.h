#pragma once
#include "stdafx.h"

//bibl.cpp
double norm(struct Vector2, struct Vector2);
double norm(struct Vector2*, struct Vector2*);
double norm(struct Vector2);
double norm(struct Vector2*);
double sign(double);
double dotprod(struct Vector2, struct Vector2);

//runge.cpp
void next_step_N(struct state_model*, struct koef_of_model*, struct surface*, double* force, double* time_left);
void next_step_no_N(struct state_model*, struct koef_of_model*, double *time);

//runge_func.cpp
struct Vector2 func_solve_acceleration(struct Vector2* Velocity, struct koef_of_model*, double* force, struct surface*);
void runge_koef(struct Vector2* solve_velocity, struct Vector2* solve_acceleration, struct koef_of_model*, struct surface*, double* force, double* step, struct runge_K* K); // Attention * &
struct Vector2 solve_koef_coord(struct runge_K*);
struct Vector2 solve_koef_velocity(struct runge_K*);

//xz.cpp
double find_earth(struct state_model*, struct koef_of_model*, struct surface*); //-2 error! We fell through the texture //-1 Touching outside a known surface //Through how many will be touching
double time_no_N(struct state_model*, struct surface*);
void hit(struct state_model*, struct koef_of_model*, struct surface*);
int touch_test(struct state_model*, struct koef_of_model*, struct surface*);
