#pragma once
#include "stdafx.h"

//bibl.cpp
// maybe remove same functions
double norm (const struct Vector2 &, const struct Vector2 &);
double norm (const struct Vector2 *, const struct Vector2 *);

double norm (const struct Vector2 &);
double norm (const struct Vector2 *);

double sign (const double);
double cos_deg (const double);
double sin_deg (const double);
double tan_deg (const double);
double dotprod (const struct Vector2 &, const struct Vector2 &);

//runge.cpp
void next_step_N (struct state_model *, struct koef_of_model *, struct surface *, double *, double *);
void next_step_no_N (struct state_model*, struct koef_of_model*, double *);

//runge_func.cpp
struct Vector2 func_solve_acceleration (const struct Vector2 *, const struct koef_of_model *, double *, struct surface *);
void runge_koef (const struct Vector2 *, const struct Vector2 *, const struct koef_of_model*, struct surface*,
				 double *, double *, struct runge_K *K); // Attention * &
struct Vector2 solve_koef_coord (const struct runge_K *);
struct Vector2 solve_koef_velocity (const struct runge_K *);

//xz.cpp
enum class touch_earth
{
	normal = 0, // Through how many will be touching
	outside_surface, // Touching outside a known surface
	fall_down_texture, // We fell through the texture
};

touch_earth find_earth (const struct state_model *, const struct koef_of_model *, const struct surface *, double *); 
double time_no_N (const struct state_model *, const struct surface *);
void hit (struct state_model*, struct koef_of_model*, const struct surface *);
int touch_test (const struct state_model *, const struct surface *);
