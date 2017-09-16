#pragma once

//bibl.cpp
double norm(const  Vector2&, const  Vector2&);
double norm(const  Vector2&);
double sign(const double);
double dotprod(const  Vector2, const  Vector2);
 Vector2 rotate_vec(const  Vector2 vec, const double phi);

//runge.cpp
int next_step_n(FILE*,  state_model* const, const  koef_of_model*, const  surface*, const double force, double* time_left, double all_time_step);
int solve_body(FILE*, state_model *, const koef_of_model *, double step_time);
void next_step_no_n(FILE*,  state_model* const, const  koef_of_model*, const  surface*, double *time_left, double all_time_step);

//runge_func.cpp
 Vector2 func_solve_acc_wheel(state_model* , const Vector2* Velocity, const  koef_of_model*, const double force, const  surface*, const bool flag_record);
void runge_koef(state_model *, const Vector2 Velocity, const Vector2 Acceleration, const koef_of_model* , const surface* , const double force, const double h, runge_K*);
 Vector2 solve_koef_coord(const  runge_K*);
 Vector2 solve_koef_velocity(const  runge_K*);
double err_runge(const Vector2 Yh, const Vector2 Yh_2);
double err_runge_y(const Vector2 Yh, const Vector2 Yh_2);

//xz.cpp
void hit( state_model*, const  koef_of_model*, const  surface*);
int touch_test(state_model* , const  koef_of_model* , const surface* , double *current_surface_height);
int speed_into_surface(const  state_model*, const  surface*);
void hit_theend_step( state_model* const , const  koef_of_model* , const surface* , const bool contact);
Vector2 center_mass(const state_model *current_model, const koef_of_model *koef_model);
double deformation_suspension(const Vector2 body, const Vector2 wheel, const koef_of_model *const koef_model);



//runge_body_func.cpp
Vector2 func_solve_acc_body(const Vector2 body, const Vector2 wheel, const koef_of_model* , state_model* );
Vector2 func_solve_acc_wheel_no_n(state_model* , const koef_of_model* , const bool flag_record);
void runge_koef_body(const Vector2 Velocity, const Vector2 Acceleration, const koef_of_model* , const double h, runge_K* K);

//Log.cpp
void print_model(FILE*, const state_model *const);
void print_new_step(FILE*);
void print_surface(FILE*, const surface *const);


//fly_runge_func
void fly_acc(state_model *, const koef_of_model * );
void fly_runge_koef(const Vector2 Velocity, const Vector2 Acceleration, const double h, runge_K* );

//wheel_function
bool transform_local_coord_to_global(state_model const* current_model);