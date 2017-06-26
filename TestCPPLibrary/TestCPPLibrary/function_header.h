#pragma once

//bibl.cpp
double norm(const struct Vector2, const struct Vector2);
double norm(const struct Vector2*, const struct Vector2*);
double norm(const struct Vector2);
double norm(const struct Vector2*);
double sign(const double);
double dotprod(const struct Vector2, const struct Vector2);

//runge.cpp
void next_step_N(struct state_model*, const struct koef_of_model*, const struct surface*, const double force, double* time_left, double all_time_step);
void next_step_no_N(struct state_model*, const struct koef_of_model*, const double time);

//runge_func.cpp
struct Vector2 func_solve_acceleration(const struct Vector2* Velocity, const struct koef_of_model*, const double force, const struct surface*);
struct Vector2 ñonversion_inertial_coordinate_system(const double val, const struct surface* current_surface);
void runge_koef(const struct Vector2* solve_velocity, const Vector2* solve_acceleration, const struct koef_of_model*, const struct surface*, const double force, const double step, struct runge_K* K); // Attention * &
struct Vector2 solve_koef_coord(const struct runge_K*);
struct Vector2 solve_koef_velocity(const struct runge_K*);

//xz.cpp
double find_earth(const struct state_model*, const struct koef_of_model*, const struct surface*); //-2 error! We fell through the texture //-1 Touching outside a known surface //Through how many will be touching
double time_no_N(const struct state_model*, const  struct surface*);
void hit(struct state_model*, const struct koef_of_model*, const struct surface*);
int touch_test(const struct state_model*, const struct koef_of_model*, const struct surface*);
