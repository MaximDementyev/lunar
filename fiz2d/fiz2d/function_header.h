#pragma once

//bibl.cpp
double norm(const struct Vector2&, const struct Vector2&);
double norm(const struct Vector2&);
double sign(const double);
double dotprod(const struct Vector2, const struct Vector2);
struct Vector2 rotate_vec(const struct Vector2 vec, const double phi);

//runge.cpp
int next_step_N(FILE*, struct state_model* const, const struct koef_of_model*, const struct surface*, const double force, double* time_left, double all_time_step);
int solve_body(FILE*, state_model *current_model, const koef_of_model *koef_model, double step_time);
void next_step_no_N(FILE*, struct state_model* const, const struct koef_of_model*, const struct surface*, double *time_left);

//runge_func.cpp
struct Vector2 func_solve_acc_wheel(state_model* current_model, const Vector2* Velocity, const struct koef_of_model*, const double force, const struct surface*, const bool flag_record);
void runge_koef(state_model *current_model, const Vector2 Velocity, const Vector2 Acceleration, const koef_of_model* koef_model, const surface* current_surface, const double force, const double h, runge_K* K);
struct Vector2 solve_koef_coord(const struct runge_K*);
struct Vector2 solve_koef_velocity(const struct runge_K*);
double err_runge(const Vector2 Yh, const Vector2 Yh_2);
double err_runge_body(const Vector2 Yh, const Vector2 Yh_2);

//xz.cpp
void hit(struct state_model*, const struct koef_of_model*, const struct surface*);
int touch_test(const state_model* current_model, const struct koef_of_model* koef_model, const surface* current_surface, double *current_surface_height);
int speed_into_surface(const struct state_model*, const struct surface*);
void hit_theend_step(struct state_model* const current_model, const struct koef_of_model* koef_model, const surface* current_surface, const bool contact);



//runge_body_func.cpp
double deformation_suspension(const Vector2  body, const Vector2 wheel, const koef_of_model *const koef_model);
Vector2 func_solve_acc_body(const Vector2 body, const Vector2 wheel, const koef_of_model* koef_model, state_model* current_model);
Vector2 func_solve_acc_wheel_noN(state_model* current_model, const koef_of_model* koef_model, const bool flag_record);
void runge_koef_body(const Vector2 Velocity, const Vector2 Acceleration, const koef_of_model* koef_model, const double h, runge_K* K);

//Log.cpp
void print_model(FILE*, const state_model *const);
void print_new_step(FILE*);
void print_surface(FILE*, const surface *const);