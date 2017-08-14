#pragma once

//bibl.cpp
double norm(const struct Vector2&, const struct Vector2&);
double norm(const struct Vector2&);
double sign(const double);
double dotprod(const struct Vector2, const struct Vector2);
struct Vector2 rotate_vec(const struct Vector2 vec, const double phi);

//runge.cpp
void next_step_N(struct state_model* const, const struct koef_of_model*, const struct surface*, const double force, double* time_left, double all_time_step);
void next_step_no_N(struct state_model* const, const struct koef_of_model*, const struct surface*, double *time_left);

//runge_func.cpp
struct Vector2 func_solve_acc_wheel(state_model* current_model, const Vector2* Velocity, const struct koef_of_model*, const double force, const struct surface*, const bool flag_record);
void runge_koef(state_model *current_model, const Vector2 Velocity, const Vector2 Acceleration, const koef_of_model* koef_model, const surface* current_surface, const double force, const double h, runge_K* K);
void solve_body(state_model *current_model, const koef_of_model *koef_model, double step_time);
struct Vector2 solve_koef_coord(const struct runge_K*);
struct Vector2 solve_koef_velocity(const struct runge_K*);

//xz.cpp
/*enum class find_earth_error
{
	normal,
	fell_through,
	touch_outside,
};
find_earth_error find_earth(const struct state_model*, const struct koef_of_model*, const struct surface*, double *); //-2 error! We fell through the texture //-1 Touching outside a known surface //Through how many will be touching
double time_no_N(const struct state_model*, const  struct surface*);*/
void hit(struct state_model*, const struct koef_of_model*, const struct surface*);
int touch_test(const state_model* current_model, const struct koef_of_model* koef_model, const surface* current_surface, double *current_surface_height);
int speed_into_surface(const struct state_model*, const struct surface*);
void hit_theend_step(struct state_model* const current_model, const struct koef_of_model* koef_model, const surface* current_surface, const bool contact);



//runge_body_func.cpp
Vector2 func_solve_acc_body(state_model* current_model, const koef_of_model* koef_model, const bool flag_record);
Vector2 func_solve_acc_wheel_noN(state_model* current_model, const koef_of_model* koef_model, const bool flag_record);
void runge_koef_body(const Vector2 Velocity, const Vector2 Acceleration, const koef_of_model* koef_model, const double h, runge_K* K);